#include <iostream>
#include "Matrices.h"

namespace Matrices
{
    Matrix::Matrix(int _rows, int _cols)
    {
        rows = _rows;
        cols = _cols;
        

        a.resize(rows);
        
        for(size_t i = 0; i < rows; i++)
        {
            a.at(i).resize(cols);
            for(size_t j = 0; j < cols; j++)
            {
                a.at(i).at(j) = 0;
            }
        }
        
        a.resize(rows,vector<double>(cols,0));
        
    }

    Matrix operator+(const Matrix& a, const Matrix& b)
    {
        if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
        {
            throw runtime_error("Error: dimesions must agree");
        }
        
        Matrix c(a.getRows(), a.getCols());
        
        for(int i = 0; i < a.getRows(); i++)
        {
            for(int j = 0; j < a.getCols(); j++)
            {
                c(i,j) = a(i,j) + b(i,j);
            }
            
        }
        
        return c;
    }
    
Matrix operator*(const Matrix& a, const Matrix& b)
{
    
    if (a.getCols() != b.getRows())
    {
        throw runtime_error("Error: dimesions must agree");
    }
    
    Matrix c(a.getRows(),b.getCols());
    
    for(int i = 0; i < a.getRows(); i++)
    {
        for(int j = 0; j < b.getCols(); j++)
        {
            for(int k = 0; k < a.getCols(); k++)
            {
                c(i,j) += a(i,k) * b(k,j);
            }
        }
        
    }
    return c;
}

bool operator==(const Matrix& a, const Matrix& b)
{
    if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
    {
        return false;
    }
    for(int i = 0; i < a.getRows(); i++)
    {
        for(int j = 0; j < a.getCols(); j++)
        {
            if(abs(a(i,j)-b(i,j)) > 0.001)
            {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const Matrix& a, const Matrix& b)
{
    if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
    {
        return true;
    }
    for(int i = 0; i < a.getRows(); i++)
    {
        for(int j = 0; j < a.getCols(); j++)
        {
            if(abs(a(i,j)-b(i,j)) > 0.001)
            {
                return true;
            }
        }
    }
    return false;
}

ostream& operator<<(ostream& os, const Matrix& a)
{
    
    for(int i = 0; i < a.getRows(); i++)
    {
        for(int j = 0; j < a.getCols(); j++)
        {
            os << setw(8) << a(i,j) << " ";
        }
        os << endl;
    }
    
    return os;
}
}

