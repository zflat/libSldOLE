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


/**
 * @brief M3dHelper::transform Transform the point by multiplying with the transform matrix.
 * Note the rotation matrix is interpreted as post-multiplication. This is inferred from the
 * documentation for IMathUtility::CreateMatrix where the lower row contains the translation vector.
 * This implies that the homogeneous is the transpose of Pre-multiplcation, column vector, based
 * transformation matrix.
 * @param pt_vals point in row vector form <x, y, z>
 * @param xT Tranformation matrix
 * @return
 */
std::vector<double> M3dHelper::transform(std::vector<double> pt_vals, IMathTransformPtr xT){

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


    /// Creata math point from given values
    pt0Ptr = makeMathPoint(pt_vals);
    if(NULL == pt0Ptr){
         qCritical () << "MathPoint not created from given vector.";
         return retval;
    }

    /// Compute the tranformation
    hr = pt0Ptr->IMultiplyTransform(xT, &pt1Ptr);

    /// Extract values from the resulting point
    VARIANT pt_resultsV;
    hr = pt1Ptr->get_ArrayData(static_cast<VARIANT *>(& pt_resultsV));
    SafeDoubleArray arr_pt1(pt_resultsV);
    for(int i=0; i<arr_pt1.getSize(); i++){
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

IMathPointPtr M3dHelper::makeMathPoint(std::vector<double> vals){
    IMathPointPtr retval = NULL;
    HRESULT hr;

    SafeDoubleArray s_vals(3);
    for(uint i=0; i<s_vals.getSize(); i++){
        s_vals[i] = vals[i];
    }
    VARIANT ptV;
    s_vals.toVARIANT(&ptV);
    LPDISPATCH pDisp;
    hr = math->CreatePoint(ptV, static_cast<IDispatch **>(&pDisp));

    if(hr != S_OK){
        qCritical() << "Could not create math point.";
    }else if(pDisp != NULL){
        hr = pDisp->QueryInterface(IID_IMathPoint, (LPVOID *)(&retval));
        if(! SUCCEEDED(hr)){
            qCritical () << "Could not create MathPoint";
        }
    }else{
        qCritical() << "Could not create math point.";
        return NULL;
    }

    return retval;
}

IMathTransformPtr M3dHelper::xformT(std::vector<double> c, double scale){
    if(c.size() != 12){
        return NULL;
    }
    HRESULT hr;

    SafeDoubleArray vals(16);
    for(uint i=0; i < vals.getSize(); i++){
        if(i<12){
            vals[i] = c[i];
        }else if(i==12){
            vals[i] = scale;
        }else{
            vals[i] = 0;
        }
    }
    IMathTransformPtr xform;
    LPDISPATCH pDisp = NULL;
    hr = math->CreateTransform(vals, &pDisp);

    if(!SUCCEEDED(hr)){
        return NULL;
    }

    hr = pDisp->QueryInterface(IID_IMathTransform, (LPVOID *)&xform);

    if(!SUCCEEDED(hr)){
        return NULL;
    }
    return xform;
}


double M3dHelper::bounded_rand(double min, double max){
    return min+((double)qrand()/ RAND_MAX)*(max-min);
}

