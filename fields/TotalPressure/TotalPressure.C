#include "TotalPressure.H"
#include "fluidThermo.H"
#include "addToRunTimeSelectionTable.H"

namespace Foam
{
namespace functionObjects
{
    // 在运行时选择表中注册
    defineTypeNameAndDebug(TotalPressure, 0);
    addToRunTimeSelectionTable(functionObject, TotalPressure, dictionary);
}
}


// calc()：计算逻辑
bool Foam::functionObjects::TotalPressure::calc()
{
    if
    (
        foundObject<volVectorField>(fieldName_) &&
        foundObject<fluidThermo>(fluidThermo::dictName)
    )
    {
        // 取热力学模型和速度场
        const fluidThermo& thermo =
            lookupObject<fluidThermo>(fluidThermo::dictName);

        const volVectorField& U =
            lookupObject<volVectorField>(fieldName_);

        // 取静压、密度（以及如果需要，可保留静温 T）
        const volScalarField& p =
            lookupObject<volScalarField>("p");

        const volScalarField& rho =
            lookupObject<volScalarField>("rho");

        // 计算 γ 场与声速 a
        volScalarField gammaF = thermo.gamma();
        volScalarField a = sqrt(gammaF * p / rho);

        // 计算 Mach 数场
        volScalarField Mach = mag(U) / a;

        // 直接用 store 写入 totalPressure，并返回 true
        return store
        (
            resultName_,
            p * pow
            (
                scalar(1.0)
              + scalar(0.5) * (gammaF - scalar(1.0)) * sqr(Mach),
                gammaF / (gammaF - scalar(1.0))
            )
        );
    }

    return false;
}


// 构造函数：绑定 controlDict 的 entry，默认输入场为 "U"
Foam::functionObjects::TotalPressure::TotalPressure
(
    const word& name,
    const Time& runTime,
    const dictionary& dict
)
:
    fieldExpression(name, runTime, dict, "U")
{
    // 输出场默认命名为 "Pt"
    setResultName("Pt", "U");
}
