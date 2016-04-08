//
//  S5.cpp
//  
//
//  Created by Lan Yao on 12/13/15.
//
//

#include "S5_Sort1NNByCommonFace_BCC.h"
#include "MatrixOperation.h"

#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <Vector>

//using Eigen::MatrixXd;
//using Eigen::VectorXd;
using namespace std;
using namespace Eigen;

#include <typeinfo>

void S5_Sort1NNByCommonFace_BCC()
{
    
    cout<<"S5_Sort1NNByCommonFace_BCC is running.\n"<<endl;

    string baseName="BCC_W_tip_20nm";
    string FileNamePoints=baseName + ".mat";
    
    fstream Points_file;
    fstream FirstNN_file;
  
    MatrixXd Points(10,3);
    MatrixXd Points2(10,3);
    Points=MatrixXd::Random(10,3);
    Points2=MatrixXd::Random(10,3);
    /////////////////////
    cout<<"Points: "<<endl;
    PrintMatrix(Points,0,10);
    cout<<"Points2: "<<endl;
    PrintMatrix(Points2,0,10);
    /////////////////////
    double maxVal,minVal;
    int r,c;
    maxVal=Points.maxCoeff(&r, &c);
    cout<<"MaxVal is: "<<maxVal<<endl;
    cout<<"MaxVal is at: "<<"["<<r<<","<<c<<"]"<<endl;

    minVal=Points.minCoeff(&r, &c);
    cout<<"minVal is: "<<minVal<<endl;
    cout<<"minVal is at: "<<"["<<r<<","<<c<<"]"<<endl;
    /////////////////////
    vector<int> indexArrayTemp={0,2,4,6,8};
    MatrixXd PointsNew(indexArrayTemp.size(),3);
    MatrixXd PointsNewTest(indexArrayTemp.size(),3);

    
    for (int i=0;i<indexArrayTemp.size();i++)
    {
        PointsNew.row(i)=Points.row(indexArrayTemp[i]);
    }
    
    cout<<"PointsNew: "<<endl;
    PrintMatrix(PointsNew,0,PointsNew.rows());
    /// Indirect Access ///
    IndirectAcess(PointsNewTest,Points,indexArrayTemp);
    cout<<"PointsNewTest: "<<endl;
    PrintMatrix(PointsNewTest,0,PointsNew.rows());
    /// Sortrows ///
    MatrixXd PointsSorted(Points.rows(),Points.cols());
    SortRowsMatrix(PointsSorted,Points,0);
    cout << "PrintPointsSorted:";
    PrintMatrix(PointsSorted,0,PointsSorted.rows());
    
    //////////////////////////
    // Assign a MatrixXd Object to a std::vector //
    int n = PointsSorted.rows();
    vector <int> v(n);
    VectorXi::Map(v.data(), n) = (PointsSorted.col(0).array()<0).cast<int>();
    for(int i=0; i<n; ++i) cout << v[i];
    cout << endl;
    
    // Assign a std::vector to a MatrixXd Object //
    vector<double> v_double(v.begin(), v.end());
    Map<MatrixXd> m(v_double.data(),10,1);
    PointsSorted.col(0)=m;
    PrintMatrix(PointsSorted,0,PointsSorted.rows());
    cout<<endl;
    cout<<PointsSorted;
    
    // Find union set between Points_Int and Points2_Int//
    MatrixXi Points_Int(10,3);
    MatrixXi Points2_Int(10,3);
    MatrixXi Points3_Int(10,3);
    
    Points_Int=(Points.array()<0).cast<int>();
    Points2_Int=(Points2.array()<0).cast<int>();
    Points3_Int=(Points2.array()==0).cast<int>();
    
    cout<<endl<<"Points_Int: "<<endl;
    PrintMatrix(Points_Int,0,Points_Int.rows());
    cout<<endl<<"Points2_Int: "<<endl;
    PrintMatrix(Points2_Int,0,Points2_Int.rows());
    cout<<endl<<"Points3_Int: "<<endl;
    PrintMatrix(Points3_Int,0,Points3_Int.rows());
    
    vector <int> v1(n);
    vector <int> v2(n);
    
    VectorXi::Map(v1.data(), n) = Points_Int.col(2);
    VectorXi::Map(v2.data(), n) = Points2_Int.col(2);
    
    cout<<endl<<"v1: "<<endl;
    for(int i=0; i<n; ++i) cout << v1[i];
    cout << endl;
    cout<<endl<<"v2: "<<endl;
    for(int i=0; i<n; ++i) cout << v2[i];
    cout << endl;
    
    set<int> s1( v1.begin(), v1.end());
    set<int> s2( v2.begin(), v2.end());
    
    cout<<endl<<"size of s1: "<<s1.size()<<endl;
    cout<<endl<<"size of s2: "<<s2.size()<<endl;
    
    v1.assign(s1.begin(),s1.end());
    v2.assign(s2.begin(),s2.end());
 
    v1.resize(s1.size());
    v2.resize(s2.size());
    
    cout<<endl<<"v1 after removed duplicate elements: "<<endl;
    for(int i=0; i<v1.size(); ++i) cout << v1[i]<<" ";
    cout << endl;
    cout<<endl<<"v2 after removed duplicate elements: "<<endl;
    for(int i=0; i<v2.size(); ++i) cout << v2[i]<<" ";
    cout << endl;
    
    int array1[v1.size()];
    int array2[v2.size()];
    
    copy(v1.begin(), v1.end(), array1);
    copy(v2.begin(), v2.end(), array2);

    
    sort(array1,array1+sizeof(array1)/sizeof(int));
    sort(array2,array2+sizeof(array2)/sizeof(int));
    
    cout<<endl<<"size of array1: "<<sizeof(array1)/sizeof(int)<<endl;
    cout<<endl<<"size of array2: "<<sizeof(array2)/sizeof(int)<<endl;
    
    cout<<endl<<"array1: "<<endl;
    for(int i=0; i<sizeof(array1)/sizeof(int); ++i) cout << array1[i]<< endl;
    cout << endl;

    cout<<endl<<"array2: "<<endl;
    for(int i=0; i<sizeof(array2)/sizeof(int); ++i) cout << array2[i]<< endl;
    
    vector<int> v_SetUnionResult(n*2);
    vector<int>::iterator it;
    
    it=set_union(array1, array1+sizeof(array1)/sizeof(int), array2, array2+sizeof(array2)/sizeof(int), v_SetUnionResult.begin());
    v_SetUnionResult.resize(it-v_SetUnionResult.begin());
    
    cout<<"size of v_SetUnionResult:"<<v_SetUnionResult.size()<<endl;
    cout<<endl<<"set union of v1 and v2: "<<endl;
    for(int i=0; i<v_SetUnionResult.size(); ++i) cout << v_SetUnionResult[i]<< endl;
    
    /// Find mean of a column ///
    cout<<"mean of Points.col(2):"<<endl<<Points.col(2).array().mean()<<endl;
    
    /// Matlab version of Find (), e.g. below is to find the Points data which first column is larger than zero ///
    cout<<endl<<"Find Points data with (Points(:,1)>0)"<<endl;
    VectorXi vecXi;
    vecXi=(Points.col(0).array()>0).cast<int>();
    cout<<endl<<"vecXi:"<<endl<<vecXi<<endl;
    cout<<endl<<"size of vecXi:"<<vecXi.size()<<endl;
    
    vector<int> v4;
    for (int i=0;i<vecXi.size();i++)
    {
        if (vecXi(i)==1)
        {
            v4.push_back(i);
        }
    }
    cout<<endl<<"v4:"<<endl;
    for(int i=0; i<v4.size(); i++) cout << v4[i]<< endl;
    cout<<endl<<"size of v4:"<<v4.size()<<endl;
    
    MatrixXd PointsByFind(v4.size(),3);
    IndirectAcess(PointsByFind,Points,v4);
    PrintMatrix(PointsByFind,0,PointsByFind.rows());
 }



