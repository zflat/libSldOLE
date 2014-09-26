#include "m3d_helper.h"

M3dHelper::M3dHelper(SldContext * sld_cont)
{
	context = sld_cont;
	context->get_swApp()->IGetMathUtility(&math);
}

M3dHelper::~M3dHelper(){
	math->Release();
	math = NULL;
}

IMathUtilityPtr M3dHelper::iptr(){
	return math;
}

std::vector<double> M3dHelper::trasform(std::vector<double> pt_vals, IMathTransformPtr xT){

    // HELP!!!
    // http://forums.codeguru.com/showthread.php?74053-Help-with-VARIANT-and-LPDISPATCH*
    // http://www.mathworks.com/matlabcentral/newsreader/view_thread/6218
    // http://stackoverflow.com/questions/3730840/how-to-create-and-initialize-safearray-of-doubles-in-c-to-pass-to-c-sharp
    // http://stackoverflow.com/questions/19839625/how-to-fill-the-safearray-with-double-datatype-values-using-safearrayputelement
    //
    // http://msdn.microsoft.com/en-us/library/ms973872.aspx
    // http://www.informit.com/articles/article.aspx?p=27219&seqNum=8
    //
    // Good question:
    // http://stackoverflow.com/questions/11977806/how-to-pass-safearray-to-com-object-through-idispatch

    std::vector<double> retval(3);
    HRESULT hr = S_OK;
    IMathPointPtr pt0Ptr = NULL;
    IMathPointPtr pt1Ptr = NULL;
    SafeDoubleArray s_vals(3);

    for(uint i=0; i<s_vals.getSize(); i++){
        s_vals[i] = pt_vals[i];
    }


    // How to make this work?
    // http://www.windows-tech.info/17/f84f874639695783.php
    // maybe? http://edn.embarcadero.com/article/22016


    SAFEARRAY * ptArr;
    hr = s_vals.toSAFEARRAY(&ptArr);
    if(hr != S_OK){
        qCritical() << "populate SAFEARRAY failed.";
    }
    if(NULL == ptArr){
        qCritical() << "Did not populate SAFEARRAY";
    }
    VARIANT ptV;
    VariantInit(&ptV);
    ptV.vt = VT_ARRAY | VT_R8;
    V_ARRAY(&ptV) = ptArr;

    LPDISPATCH p0_Disp;
    //hr = math->CreatePoint(static_cast<VARIANT>(s_vals), static_cast<IDispatch**>(&pt0Disp));
    hr = math->CreatePoint(ptV, static_cast<IDispatch **>(&p0_Disp));

    if(hr != S_OK){
        qCritical() << "Could not create math point.";
    }else if(p0_Disp != NULL){
        hr = p0_Disp->QueryInterface(IID_IMathPoint, (LPVOID *)&pt0Ptr);
        if(! SUCCEEDED(hr)){
            qCritical () << "Could not create MathPoint";
        }
    }else{
        return retval;
    }

    if(NULL == pt0Ptr){
        return retval;
    }


    pt0Ptr->IMultiplyTransform(xT, &pt1Ptr);


    VARIANT pt_resultsV;
    pt1Ptr->get_ArrayData(static_cast<VARIANT *>(& pt_resultsV));

    SafeDoubleArray arr_pt1(pt_resultsV);
    for(int i=0; i<arr_pt1.getSize(); i++){
        qDebug() << arr_pt1[i];
        retval[i] = arr_pt1[i];
    }


    /// Cleanup resources
    pt0Ptr->Release();
    pt1Ptr->Release();

    return retval;
}

std::vector<double> M3dHelper::warp(std::vector<double> pt_0, IMathTransformPtr xform){
    std::vector<double> v;
    return v;
}

std::vector<double> M3dHelper::makeVector( double * data, int size ){
    //return std::vector<double>(data, data + sizeof(data) / sizeof(data[0]));
    std::vector<double>v;
    for(int i=0; i<size; i++){v.push_back(data[i]);}
    return v;
}

IMathTransformPtr M3dHelper::xformI(){
    double vals[12] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0};
    return xformT(makeVector(vals, 12), 1.0);
}



IMathTransformPtr M3dHelper::xformT(std::vector<double> c, double scale){
    if(c.size() != 12){
        return NULL;
    }
/*
    double vect_vals_x[3] = {c[0], c[1], c[2]};
    double vect_vals_y[3] = {c[3], c[4], c[5]};
    double vect_vals_z[3] = {c[6], c[7], c[8]};
    double vect_vals_trans[3] = {c[9], c[10], c[11]};

    IMathVectorPtr ivect_x;
    IMathVectorPtr ivect_y;
    IMathVectorPtr ivect_z;
    IMathVectorPtr ivect_trans;

    math->ICreateVector(vect_vals_x, &ivect_x);
    math->ICreateVector(vect_vals_y, &ivect_y);
    math->ICreateVector(vect_vals_z, &ivect_z);
    math->ICreateVector(vect_vals_trans, &ivect_trans);
    //math->ComposeTransform(ivect_x, ivect_y, ivect_z, ivect_trans, scale, &xform);
*/

    double vals[16];
    for(int i=0; i<16; i++){
        if(i<12){
            vals[i] = c[i];
        }else if(i==12){
            vals[i] = scale;
        }else{
            vals[i] = 0;
        }
    }
    IMathTransformPtr xform;
    math->ICreateTransform(vals, &xform);
    return xform;
}
