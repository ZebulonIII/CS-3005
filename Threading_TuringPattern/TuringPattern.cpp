#include <algorithm>
#include <random>
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
	if (dx > 0 && dt > 0 && Da > 0 && Db > 0) {
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
		: 1.;
}
double TuringPattern::getPrevValue(const int& row, const int& column, const int& species) const {
	return ((species == 0 || species == 1) && indexValid(row, column))
		? this->mData[mPrev][species][index(row, column)]
		: 1.;
}
void TuringPattern::setCurrValue(const int& row, const int& column, const int& species, const double& value) {
	if ((species == 0 || species == 1) && indexValid(row, column))
		this->mData[mPrev][species][index(row, column)] = value;
}
void TuringPattern::setPrevValue(const int& row, const int& column, const int& species, const double& value) {
	if ((species == 0 || species == 1) && indexValid(row, column))
		this->mData[mPrev][species][index(row, column)] = value;
}
void TuringPattern::swapCurrPrev() {
	std::swap(mCurr, mPrev);
}
void TuringPattern::randomizeValues() {
	int big_value = 1234567;
	double random_value;
	for (int species = 0; species < 2; species++)
		for (int row = 0; row < getHeight(); row++)
			for (int col = 0; col < getWidth(); col++) {
				random_value = ((std::rand() % big_value) - (big_value / 2)) / (50. * big_value);
				setCurrValue(row, col, species, random_value);
				setPrevValue(row, col, species, random_value);
			}
}
double TuringPattern::calculateDivergence(const int& row, const int& column, const int& species) {
	double deltaA = -4.0 * getPrevValue(row, column, species)
		+ getPrevValue(row - 1, column, species)
		+ getPrevValue(row + 1, column, species)
		+ getPrevValue(row, column - 1, species)
		+ getPrevValue(row, column + 1, species);
	return deltaA / (mDx * mDx);
}
double TuringPattern::calculateCurrValue(const int& row, const int& column, const int& species) {
	return getPrevValue(row, column, species) + mDt * mDa * calculateDivergence(row, column, species);
}
void TuringPattern::updateValues(const int& steps) {
	double value;
	for (int i = 0; i < steps; i++) {
		swapCurrPrev();
		for (int species = 0; species < 2; species++)
			for (int row = 0; row < getHeight(); row++)
				for (int col = 0; col < getWidth(); col++) {
					value = calculateCurrValue(row, col, species);
					setCurrValue(row, col, species, value);
				}
	}
}
double TuringPattern::Ra(const double& a, const double& b) const {
	return a - a*a*a - b + mAlpha;
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
			diff = std::abs(getCurrValue(row, col, 0) - getCurrValue(row, col, 1));
			if (diff < mMinDifference)
				mMinDifference = diff;
			if (diff > mMaxDifference)
				mMaxDifference = diff;
		}
}
void TuringPattern::setGridSize(const int& height, const int& width) {
	NumberGrid::setGridSize(height, width);
	// need more
}
int TuringPattern::calculateNumber(const int& row, const int& column) const {
	double diff = std::abs(getCurrValue(row, column, 0) - getCurrValue(row, column, 1));
	double s = (diff - mMinDifference) / (mMaxDifference - mMinDifference);
	int n = 1 + (mMaxDifference - 2) * s;
	return n;
}
void TuringPattern::calculateAllNumbers() {
	findMinMaxDifference();
	ThreadedGrid::calculateAllNumbers();
}
