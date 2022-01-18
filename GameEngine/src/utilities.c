#include "utilities.h"

hmm_quaternion EulerToQuat(hmm_vec3 euler)
{
    double c1 = HMM_CosF(euler.Y/2);
    double s1 = HMM_SinF(euler.Y/2);
    double c2 = HMM_CosF(euler.X/2);
    double s2 = HMM_SinF(euler.X/2);
    double c3 = HMM_CosF(euler.Z/2);
    double s3 = HMM_SinF(euler.Z/2);
    double c1c2 = c1*c2;
    double s1s2 = s1*s2;
    hmm_quaternion out;
    out.W =c1c2*c3 - s1s2*s3;
  	out.X =c1c2*s3 + s1s2*c3;
	out.Y =s1*c2*c3 + c1*s2*s3;
	out.Z =c1*s2*c3 - s1*c2*s3;
    return out;
}