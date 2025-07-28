# Total-temperature-and-total-pressure-function-objects
Total Temperature and Total Pressure Calculations for Compressible Flow in OpenFOAM-v2212


//---------YMC：Compile function object in OpenFOAM-v2212 environment------------//

1. wclean

2. wmake


//-----YMC：Add the following function objects to the system/controldict file.----//

functions
{
 
    calcTt 
    {
        type    TotalTemperature;
        libs    ("ymcfieldFunctionObjects.so");
    }

    calcPt
    {
        type    TotalPressure;
        libs    ("ymcfieldFunctionObjects.so");
    }


}
