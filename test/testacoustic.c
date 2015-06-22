#include "schnaps.h"
#include <stdio.h>
#include <assert.h>
#include "test.h"
#include <string.h>

int TestAcoustic(void) {
  field f;
  init_empty_field(&f);

  f.model.cfl = 0.05;
  f.model.m = 4; // only one conservative variable
  f.model.NumFlux = AcousticNumFlux;
  f.model.BoundaryFlux = AcousticBoundaryFlux;
  f.model.InitData = AcousticInitData;
  f.model.ImposedData = AcousticImposedData;
  f.varindex = GenericVarindex;

  f.interp.interp_param[0] = f.model.m; // _M
  f.interp.interp_param[1] = 3; // x direction degree
  f.interp.interp_param[2] = 3; // y direction degree
  f.interp.interp_param[3] = 0; // z direction degree
  f.interp.interp_param[4] = 4; // x direction refinement
  f.interp.interp_param[5] = 4; // y direction refinement
  f.interp.interp_param[6] = 1; // z direction refinement

  // Read the gmsh file
  ReadMacroMesh(&(f.macromesh), "disque.msh");
  Detect2DMacroMesh(&(f.macromesh));
  assert(f.macromesh.is2d);

  BuildConnectivity(&(f.macromesh));

  // AffineMapMacroMesh(&(f.macromesh));

  // Prepare the initial fields
  Initfield(&f);
  CheckMacroMesh(&(f.macromesh), f.interp.interp_param + 1);
  return
  printf("cfl param =%f\n", f.hmin);

  real tmax = 0.1;
  real dt = 0;
  f.vmax = 0.1;
  if(dt <= 0.0)
    dt = set_dt(&f);
  RK2(&f, tmax, dt);

  // Save the results and the error
  Plotfield(0, false, &f, NULL, "dgvisu.msh");
  Plotfield(0, true, &f, "Error", "dgerror.msh");

  real dd = L2error(&f);
 
  printf("erreur L2=%f\n", dd);
  return 0;
};

int main(void) {
  int resu = TestAcoustic();
  if (resu) 
    printf("Test OK!\n");
  else 
    printf("Test failed !\n");
  return !resu;
}