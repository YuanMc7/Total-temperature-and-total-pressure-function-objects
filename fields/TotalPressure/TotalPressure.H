#ifndef functionObjects_TotalPressure_H
#define functionObjects_TotalPressure_H

#include "fieldExpression.H"

namespace Foam
{
namespace functionObjects
{

class TotalPressure
:
    public fieldExpression
{
    // 计算总压场
    virtual bool calc();

public:

    TypeName("TotalPressure");

    TotalPressure
    (
        const word& name,
        const Time& runTime,
        const dictionary& dict
    );

    TotalPressure(const TotalPressure&) = delete;
    void operator=(const TotalPressure&) = delete;

    virtual ~TotalPressure() = default;
};

} // namespace functionObjects
} // namespace Foam

#endif
