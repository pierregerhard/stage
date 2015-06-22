#ifndef _ACOUSTIC_H
#define _ACOUSTIC_H

//! \brief The particular flux for the maxwell2d model
//! \param[in] wL, wR : left and right states
//! \param[in] vn : normal vector
//! \param[out] flux : the flux
void AcousticNumFlux(real *wL, real *wR, real *vn, 
		      real *flux);

//! \brief The particular imposed data for the maxwell2d model
//! \param[in] x, t : space and time position
//! \param[out] w : imposed state at point x and time t

void AcousticImposedData(const real * x, const real t, real *w);


//! \brief The particular boundary flux for the maxwell2d model
//! \param[in] x : space position
//! \param[in] t : time
//! \param[in] wL : left state
//! \param[in] vn : normal vector
//! \param[out] flux : the flux

void AcousticBoundaryFlux(real *x, real t, real *wL, 
			     real *vn, real *flux);


//! \brief The particular init data for the maxwell2d model
//! \param[in] x : space position
//! \param[out] w : init state at point x
void AcousticInitData(real *x, real *w);

#endif
