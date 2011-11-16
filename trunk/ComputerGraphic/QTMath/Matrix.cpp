#include "Matrix.h"

CMatrix::CMatrix(int row, int col): m_irow(row), m_icol(col) {
	m_fdata = new float[row*col];
	for (int i=0;i<m_irow*m_icol;i++)
		if (i%m_icol == i/m_icol)
			m_fdata[i] = 1.0f;
		else
			m_fdata[i] = 0.0f;
}

CMatrix::CMatrix(): m_irow(0), m_icol(0), m_fdata(0) {
}

CMatrix::CMatrix(float *arr, int row, int col): m_fdata(arr), m_irow(row), m_icol(col) {
}

int CMatrix::row() {
	return m_irow;
}

int CMatrix::col() {
	return m_icol;
}

float* CMatrix::getData() {
	return m_fdata;
}

void CMatrix::loadIdentity() {
	for (int i=0;i<m_irow*m_icol;i++)
		if (i%m_icol == i/m_icol)
			m_fdata[i] = 1.0f;
		else
			m_fdata[i] = 0.0f;
}

void CMatrix::getfromMatrix(void *arr, int row, int col, bool makeTranspose) {
	m_irow = row;
	m_icol = col;
	int size = m_irow * m_icol;
	m_fdata = new float[size];
	if (makeTranspose) {
		for(int i = 0; i < m_irow; i++)
			for(int j = 0; j < m_icol; j++)
				m_fdata[j*m_icol + i] = *( (float*)(  (float**)arr + i*m_icol ) + j);
		m_irow = col;
		m_icol = row;
	}
	else {
		for(int i = 0; i < m_irow; i++)
			for(int j = 0; j < m_icol; j++)
				m_fdata[i*m_icol + j] = *( (float*)(  (float**)arr + i*m_icol ) + j);
	}
}

void CMatrix::makeTranspose() {
	float *res = new float[m_irow * m_icol];
	for(int i = 0; i < m_irow; i++) {
		for(int j = 0; j < m_icol; j++)
			res[j*m_irow  + i] = m_fdata[i*m_icol + j];
	}
	int tmp = m_irow;
	m_irow = m_icol;
	m_icol = tmp;
	delete []m_fdata;
	m_fdata = res;
}

CMatrix::~CMatrix() {
	if(m_fdata) delete[] m_fdata;
}

void CMatrix::PrintInfo() {
	int size = m_irow * m_icol;
	printf("\n----------------------\n");
	for(int i=0; i<size; i++) {
		if (i%m_icol == 0)
			printf("\n");
		printf("%.2f ",m_fdata[i]);
	}
}

void CMatrix::multMatrix(const CMatrix *op) {
	if (!op) return;

	int mid = op->m_irow;
	if (mid != this->m_icol) return;

	int newcol = op->m_icol, newrow = this->m_irow;

	float *res = new float[op->m_icol*this->m_irow];
	for(int i = 0; i < newrow; i++)
		for(int j = 0; j < newcol; j++) {
			float val = 0.0f;
			for(int k=0;k<mid;k++)
				val+=m_fdata[i*m_icol+k] * op->m_fdata[k*op->m_icol + j];
			res[i*newcol+j] = val;
		}
	delete []m_fdata;
	m_fdata = res;
	m_icol = newcol;
}

void CMatrix::multMatrix(const CMatrix &op) {
}