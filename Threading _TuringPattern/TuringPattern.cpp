#include <algorithm>
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
double getAlpha() const {
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

}
double TuringPattern::getPrevValue(const int& row, const int& column, const int& species) const;
void TuringPattern::setCurrValue(const int& row, const int& column, const int& species, const double& value);
void TuringPattern::setPrevValue(const int& row, const int& column, const int& species, const double& value);
void TuringPattern::swapCurrPrev() {
	std::swap(mCurr, mPrev);
}
void TuringPattern::randomizeValues();
double TuringPattern::calculateDivergence(const int& row, const int& column, const int& species);
double TuringPattern::calculateCurrValue(const int& row, const int& column, const int& species);
void TuringPattern::updateValues(const int& steps);
double TuringPattern::Ra(const double& a, const double& b) const;
double TuringPattern::Rb(const double& a, const double& b) const;
void TuringPattern::findMinMaxDifference() {
	mMinDifference = 1.0e10;
	mMaxDifference = -1.0e10;

	for (int i = 0; i < mData.size(); i++)

}
virtual void TuringPattern::setGridSize(const int& height, const int& width) {
	NumberGrid::setGridSize(height, width);
	mData.resize()
}
virtual int TuringPattern::calculateNumber(const int& row, const int& column) const;
virtual void TuringPattern::calculateAllNumbers();