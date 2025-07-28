#include "TotalTemperature.H"
#include "fluidThermo.H"
#include "addToRunTimeSelectionTable.H"

namespace Foam
{
namespace functionObjects
{
    // 注册到 run-time selection table
    defineTypeNameAndDebug(TotalTemperature, 0);
    addToRunTimeSelectionTable(functionObject, TotalTemperature, dictionary);
}
}


// calc()：计算逻辑
bool Foam::functionObjects::TotalTemperature::calc()
{
    if
    (
        foundObject<volVectorField>(fieldName_) &&
        foundObject<fluidThermo>(fluidThermo::dictName)
    )
    {
        // 获取 thermo model 和速度场 U
        const fluidThermo& thermo =
            lookupObject<fluidThermo>(fluidThermo::dictName);

        const volVectorField& U =
            lookupObject<volVectorField>(fieldName_);

        // 获取静压、静温、密度
        const volScalarField& p =
            lookupObject<volScalarField>("p");

        const volScalarField& T =
            lookupObject<volScalarField>("T");

        const volScalarField& rho =
            lookupObject<volScalarField>("rho");

        // 计算 γ 场和声速 a = sqrt(γ·p/ρ)
        volScalarField gammaF = thermo.gamma();
        volScalarField a = sqrt(gammaF * p / rho);

        // Mach 数场 Ma = |U|/a
        volScalarField Mach = mag(U) / a;

        // 直接通过 store 写入总温场
        return store
        (
            resultName_,
            T * ( scalar(1.0)
                + scalar(0.5) * (gammaF - scalar(1.0)) * sqr(Mach)
              )
        );
    }

    return false;
}


// 构造函数：绑定 controlDict entry，默认输入场 "U"
Foam::functionObjects::TotalTemperature::TotalTemperature
(
    const word& name,
    const Time& runTime,
    const dictionary& dict
)
:
    fieldExpression(name, runTime, dict, "U")
{
    // 默认输出场名 "Tt"
    setResultName("Tt", "U");
}
