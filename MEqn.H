Info << "Solving biomass equation (M)" << endl;

fvScalarMatrix MEqn
(
    fvm::ddt(M)
  - fvm::laplacian(d2, M, "laplacian(d2,M)")
  ==
    fvm::Sp(K3 * C / (K2 + C), M)
  - fvm::Sp(K4, M)
);

solve(MEqn);

dimensionedScalar ddtM = gMax(mag(fvc::ddt(M)())()) / (gMax(M) + SMALL);
Info << "Max relative ddt(M): " << ddtM.value() << endl;
