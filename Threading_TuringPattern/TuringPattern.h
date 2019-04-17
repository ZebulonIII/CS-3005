#ifndef _TURING_PATTERN_H_
#define _TURING_PATTERN_H_

#include <vector>
#include "ThreadedGrid.h"

class TuringPattern : public ThreadedGrid {
public:
	TuringPattern();
	double getDx() const;
	double getDt() const;
	double getAlpha() const;
	double getBeta() const;
	double getDa() const;
	double getDb() const;
	void setParameters(const double& dx, const double& dt, const double& alpha, const double& beta, const double& Da, const double& Db);
	double getCurrValue(const int& row, const int& column, const int& species) const;
	double getPrevValue(const int& row, const int& column, const int& species) const;
	void setCurrValue(const int& row, const int& column, const int& species, const double& value);
	void setPrevValue(const int& row, const int& column, const int& species, const double& value);
	void swapCurrPrev();
	void randomizeValues();
	double calculateDivergence(const int& row, const int& column, const int& species);
	double calculateCurrValue(const int& row, const int& column, const int& species);
	void updateValues(const int& steps);
	double Ra(const double& a, const double& b) const;
	double Rb(const double& a, const double& b) const;
	void findMinMaxDifference();
	virtual void setGridSize(const int& height, const int& width);
	virtual int calculateNumber(const int& row, const int& column) const;
	virtual void calculateAllNumbers();
private:
	std::vector<std::vector<std::vector<double> > > mData;
	int mCurr, mPrev;
	double mDx, mDt;
	double mAlpha, mBeta;
	double mDa, mDb;
	double mMinDifference, mMaxDifference;

	void worker_UpdateValues(const int& species);
};

#endif