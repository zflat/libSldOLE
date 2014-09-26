#ifndef M3D_HELPER_H
#define M3D_HELPER_H

#include "libsldole_global.h"
#include "sldcontext.h"
#include "smartvars.h"

/**
 * @brief The M3dHelper class is a wrapper for IMathUtility
 */
class LIBSLDOLESHARED_EXPORT M3dHelper
{
public:
    M3dHelper(SldContext * sld_cont);
    ~M3dHelper();
    IMathUtilityPtr iptr();

	/**
	* Rotate, Scale and Translate (Affine transformation)
	*/
    std::vector<double> trasform(std::vector<double> pt_0, IMathTransformPtr xform);
    
	/**
	* Rotate, Scale only
	*/
    std::vector<double> warp(std::vector<double> pt_0, IMathTransformPtr xform);

    static std::vector<double> makeVector( double * data, int size );

    IMathTransformPtr xformI();
    IMathTransformPtr xformT(std::vector<double> rot_trans, double scale = 1);

    
protected:
    SldContext * context;
	IMathUtilityPtr math;
};

#endif // M3D_HELPER_H
