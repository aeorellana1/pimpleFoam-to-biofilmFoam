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

// phi / porosity
const surfaceScalarField& phiByPorosity = phi / (fvc::interpolate(porosity) + VSMALL);


IOdictionary transportProperties
(
    IOobject("transportProperties", runTime.constant(), mesh, IOobject::MUST_READ, IOobject::NO_WRITE)
);

// Parámetros biológicos
dimensionedScalar K1  (transportProperties.lookup("K1"));
dimensionedScalar K2  (transportProperties.lookup("K2"));
dimensionedScalar K3  (transportProperties.lookup("K3"));
dimensionedScalar K4  (transportProperties.lookup("K4"));

dimensionedScalar kd  (transportProperties.lookup("kd"));
dimensionedScalar D_M (transportProperties.lookup("D_M"));

