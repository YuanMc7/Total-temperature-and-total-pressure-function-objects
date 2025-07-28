#ifndef functionObjects_TotalTemperature_H
#define functionObjects_TotalTemperature_H

#include "fieldExpression.H"

namespace Foam
{
namespace functionObjects
{

class TotalTemperature
:
    public fieldExpression
{
    // Private Member Functions

    // 计算总温场
    virtual bool calc();

public:

    // Runtime type info
    TypeName("TotalTemperature");

    // 构造函数
    TotalTemperature
    (
        const word& name,
        const Time& runTime,
        const dictionary& dict
    );

    // 禁止拷贝
    TotalTemperature(const TotalTemperature&) = delete;
    void operator=(const TotalTemperature&) = delete;

    // 析构
    virtual ~TotalTemperature() = default;
};

} // namespace functionObjects
} // namespace Foam

#endif
