##Agregar C, M, porosidad, difusividad del sustrato y parametros biologicos, en el mismo archivo, crear transport properties
**gedit createFieldsBiofilm.H**: 
Info << "Reading field C (substrate)" << endl;
volScalarField C
(
    IOobject("C", runTime.timeName(), mesh, IOobject::MUST_READ, IOobject::AUTO_WRITE),
    mesh
);

Info << "Reading field M (biomass)" << endl;
volScalarField M
(
    IOobject("M", runTime.timeName(), mesh, IOobject::MUST_READ, IOobject::AUTO_WRITE),
    mesh
);

Info << "Reading porosity field" << endl;
volScalarField porosity
(
    IOobject("porosity", runTime.timeName(), mesh, IOobject::MUST_READ, IOobject::AUTO_WRITE),
    mesh
);

Info << "Reading d1 (substrate diffusivity field)" << endl;
volScalarField d1
(
    IOobject("d1", runTime.timeName(), mesh, IOobject::MUST_READ, IOobject::AUTO_WRITE),
    mesh
);
Info << "Reading d2 (biomass diffusivity field)" << endl;
volScalarField d2
(
    IOobject("d2", runTime.timeName(), mesh, IOobject::MUST_READ, IOobject::AUTO_WRITE),
    mesh
);
// phi / interpolated porosity (safe version)
tmp<surfaceScalarField> tPhiByPorosity = phi / (fvc::interpolate(porosity) + VSMALL);
const surfaceScalarField& phiByPorosity = tPhiByPorosity();

// Read transport and kinetic parameters from dictionary
IOdictionary transportProperties
(
    IOobject("transportProperties", runTime.constant(), mesh, IOobject::MUST_READ, IOobject::NO_WRITE)
);

// Biological kinetic parameters
dimensionedScalar K1  (transportProperties.lookupEntry("K1")());
dimensionedScalar K2  (transportProperties.lookupEntry("K2")());
dimensionedScalar kd  (transportProperties.lookupEntry("kd")());
dimensionedScalar D_M (transportProperties.lookupEntry("D_M")());
dimensionedScalar K3  (transportProperties.lookup("K3"));
dimensionedScalar K4  (transportProperties.lookup("K4"));


##Despues de eso agregar en pimpe_bio.C 
#include "createFieldsBiofilm.H" justo debajo de #include "createFields.H"
#include "CEqn.H" debajo de #include "correctPhi.H"
Y debajo de CEqn.H  #include "MEqn.H"

**Crear  CEqn.H**  :
fvScalarMatrix CEqn
(
    fvm::ddt(porosity,C)
    + porosity * fvm::div(phiByPorosity, C)
    - fvm::laplacian(d1*porosity, C)
    ==
    - fvm::Sp(K1*M/(K2+C), C)
);

solve(CEqn);

dimensionedScalar ddtC = gMax(mag(fvc::ddt(C)())()) / (gMax(C) + SMALL);

**crear MEqn.H**:
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


