#include <algorithm>
#include <utility>
#include <random>
#include <thread>
#include <fstream>
#include "TuringPattern.h"

TuringPattern::TuringPattern() :
	ThreadedGrid(), mCurr(0), mPrev(1), mDx(1.0), mDt(0.001), mAlpha(-0.005),
	mBeta(10.0), mDa(1.0), mDb(100.0), mMinDifference(1.0e10), mMaxDifference(-1.0e10) {
	setGridSize(100, 100);
}

double TuringPattern::getDx() const {
	return mDx;
}
double TuringPattern::getDt() const {
	return mDt;
}
double TuringPattern::getAlpha() const {
	return mAlpha;
}
double TuringPattern::getBeta() const {
	return mBeta;
}
double TuringPattern::getDa() const {
	return mDa;
}
double TuringPattern::getDb() const {
	return mDb;
}
void TuringPattern::setParameters(const double& dx, const double& dt, const double& alpha, const double& beta, const double& Da, const double& Db) {
	if (dx > 0. && dt > 0. && Da > 0. && Db > 0.) {
		mDx = dx;
		mDt = dt;
		mAlpha = alpha;
		mBeta = beta;
		mDa = Da;
		mDb = Db;
	}
}
double TuringPattern::getCurrValue(const int& row, const int& column, const int& species) const {
	return ((species == 0 || species == 1) && indexValid(row, column))
		? this->mData[mCurr][species][index(row, column)]
		: 0.;
}
double TuringPattern::getPrevValue(const int& row, const int& column, const int& species) const {
	return ((species == 0 || species == 1) && indexValid(row, column))
		? this->mData[mPrev][species][index(row, column)]
		: 0.;
}
void TuringPattern::setCurrValue(const int& row, const int& column, const int& species, const double& value) {
	if ((species == 0 || species == 1) && indexValid(row, column))
		this->mData[mCurr][species][index(row, column)] = value;
}
void TuringPattern::setPrevValue(const int& row, const int& column, const int& species, const double& value) {
	if ((species == 0 || species == 1) && indexValid(row, column))
		this->mData[mPrev][species][index(row, column)] = value;
}
void TuringPattern::swapCurrPrev() {
	std::swap(mCurr, mPrev);
}
void TuringPattern::worker_randomizeValues() {
	int big_value = 1234567;
	double random_value;
	std::vector<int> work;
	work.clear();

	while (!mWorkQueue.empty()) {
		mWorkQueue.pop_back(work, 1);

		int row = work[0];
		for (int col = 0; col < getWidth(); col++)
			for (int species = 0; species < 2; species++) {
				random_value = ((std::rand() % big_value) - (big_value / 2.)) / (50. * big_value);
				setCurrValue(row, col, species, random_value);
				setPrevValue(row, col, species, random_value);
		}
		work.clear();
	}
}
void TuringPattern::randomizeValues() {
	mWorkQueue.resize(getHeight());
	for (int i = 0; i < getHeight(); i++)
		mWorkQueue.push_back(i);

	static int n = getNumThreads();
	std::thread* threads = new std::thread[n];

	for (unsigned int i = 0; i < getNumThreads(); i++)
		threads[i] = std::thread(&TuringPattern::worker_randomizeValues, this);

	for (unsigned int i = 0; i < getNumThreads(); i++)
		threads[i].join();

	delete[] threads;
}
/*void TuringPattern::randomizeValues() {
	int big_value = 1234567;
	double random_value;
	for (int species = 0; species < 2; species++)
		for (int row = 0; row < getHeight(); row++)
			for (int col = 0; col < getWidth(); col++) {
				random_value = ((std::rand() % big_value) - (big_value / 2.)) / (50. * big_value);
				setCurrValue(row, col, species, random_value);
				setPrevValue(row, col, species, random_value);
			}
}*/
double TuringPattern::calculateDivergence(const int& row, const int& column, const int& species) {
	double delta = -4.0 * getPrevValue(row, column, species)
		+ getPrevValue((row - 1 >= 0) ? row - 1 : getHeight() - 1, column, species)
		+ getPrevValue((row + 1 < getHeight()) ? row + 1 : 0, column, species)
		+ getPrevValue(row, (column - 1 >= 0 ) ? column - 1 : getWidth() - 1, species)
		+ getPrevValue(row, (column + 1 < getWidth()) ? column + 1 : 0, species);
	return delta / (mDx * mDx);
}
double TuringPattern::calculateCurrValue(const int& row, const int& column, const int& species) {
	double Ap = getPrevValue(row, column, 0);
	double Bp = getPrevValue(row, column, 1);
	double divergence = calculateDivergence(row, column, species);

	return (species == 0)
		? Ap + mDt * mDa * divergence + mDt * Ra(Ap, Bp)
		: Bp + mDt * mDb * divergence + mDt * Rb(Ap, Bp);
}
void TuringPattern::worker_updateValues(const int& species) {
	for (int row = 0; row < getHeight(); row++)
		for (int col = 0; col < getWidth(); col++)
			setCurrValue(row, col, species, calculateCurrValue(row, col, species));
}
/*void TuringPattern::updateValues(const int& steps) {
	std::thread threads[2];

	//swapCurrPrev();
	for (int step = 0; step < steps; step++) {
		swapCurrPrev();

		threads[0] = std::thread(&TuringPattern::worker_updateValues, this, 0);
		threads[1] = std::thread(&TuringPattern::worker_updateValues, this, 1);

		threads[0].join();
		threads[1].join();
	}
}*/
void TuringPattern::updateValues(const int& steps) {
	for (int i = 0; i < steps; i++) {
		swapCurrPrev();
		for (int species = 0; species < 2; species++)
			for (int row = 0; row < getHeight(); row++)
				for (int col = 0; col < getWidth(); col++)
					setCurrValue(row, col, species, calculateCurrValue(row, col, species));
	}
}
double TuringPattern::Ra(const double& a, const double& b) const {
	return a - (a*a*a) - b + mAlpha;
}
double TuringPattern::Rb(const double& a, const double& b) const {
	return (a - b) * mBeta;
}
void TuringPattern::findMinMaxDifference() {
	mMinDifference = 1.0e10;
	mMaxDifference = -1.0e10;

	double diff;
	for (int row = 0; row < getHeight(); row++)
		for (int col = 0; col < getWidth(); col++) {
			diff = getCurrValue(row, col, 0) - getCurrValue(row, col, 1);
			if (diff < mMinDifference)
				mMinDifference = diff;
			if (diff > mMaxDifference)
				mMaxDifference = diff;
		}
}
void TuringPattern::setGridSize(const int& height, const int& width) {
	if (height > 0 && width > 0) {
		NumberGrid::setGridSize(height, width);

		size_t size = height * width;
		this->mData.resize(2);
		for (int i = 0; i < 2; i++)
			this->mData[i].resize(2);
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				this->mData[i][j].resize(size);
	}
}
int TuringPattern::calculateNumber(const int& row, const int& column) const {
	double diff = getCurrValue(row, column, 0) - getCurrValue(row, column, 1);
	double s = (diff - mMinDifference) / (mMaxDifference - mMinDifference);
	return 1 + (getMaxNumber() - 2.) * s;
}
void TuringPattern::calculateAllNumbers() {
	findMinMaxDifference();
	ThreadedGrid::calculateAllNumbers();
}
/*void TuringPattern::worker_UpdateValues(const int& species) {
	std::vector<int> value;

	while (!mWorkQueue.empty()) {
		value.clear();
		mWorkQueue.pop_back(value, 1);

		int i = value[0];
		for (int j = 0; j < getWidth(); j++)
			setCurrValue(i, j, species, calculateCurrValue(i, j, species));
	}
}
void TuringPattern::updateValues(const int& steps) {
	std::ofstream output("file.txt", std::ios::app);
	output << getNumThreads() << "\n";
	output.close();

	//setNumThreads(8);
	std::thread threads[getNumThreads()];

	// vector to copy into work queue
	std::vector<int> work(getHeight());
	for (int i = 0; i < getHeight(); i++)
		work[i] = i;

	for (int step = 0; step < steps; step++) {
		swapCurrPrev();

		mWorkQueue.resize(getHeight());
		mWorkQueue.push_back(work);

		for (int species = 0; species < 2; species++) {
			for (unsigned int i = 0; i < getNumThreads(); i++)
				threads[i] = std::thread(&TuringPattern::worker_UpdateValues, this, std::ref(species));

			for (unsigned int i = 0; i < getNumThreads(); i++)
				threads[i].join();
		}
	}
}*/
