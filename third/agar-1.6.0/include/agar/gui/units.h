/*	Public domain	*/

#ifndef _AGAR_WIDGET_UNITS_H_
#define _AGAR_WIDGET_UNITS_H_

#include <agar/gui/begin.h>

typedef struct ag_unit {
	char *_Nullable key;		/* Key (or list terminator) */
	char *_Nonnull abbr;		/* Abbreviated symbol */
	char *_Nonnull name;		/* Long name */
	double divider;			/* Conversion factor (linear) */
} AG_Unit;

typedef struct ag_unit_nl {
	AG_Unit unit;						/* Inherit */
	double (*_Nonnull func)(double, int);
} AG_UnitNL;

#define AG_UNIT(unit)    ((AG_Unit *)(unit))
#define AG_UNIT_NL(unit) ((AG_UnitNL *)(unit))

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC double AG_UnitFahrenheit(double, int);
extern DECLSPEC double AG_UnitCelsius(double, int);
extern DECLSPEC const AG_Unit *_Nonnull agUnitGroups[];
extern DECLSPEC const char *_Nullable agUnitGroupNames[];
extern DECLSPEC const int agnUnitGroups;
extern DECLSPEC const AG_Unit agIdentityUnit[];
extern DECLSPEC const AG_Unit agLengthUnits[];
extern DECLSPEC const AG_Unit agAngleUnits[];
extern DECLSPEC const AG_Unit agPercentageUnits[];
extern DECLSPEC const AG_Unit agVideoUnits[];
extern DECLSPEC const AG_Unit agAreaUnits[];
extern DECLSPEC const AG_Unit agVolumeUnits[];
extern DECLSPEC const AG_Unit agSpeedUnits[];
extern DECLSPEC const AG_Unit agMassUnits[];
extern DECLSPEC const AG_Unit agTimeUnits[];
extern DECLSPEC const AG_Unit agCurrentUnits[];
extern DECLSPEC const AG_UnitNL agTemperatureUnits[];
extern DECLSPEC const AG_Unit agSubstanceAmountUnits[];
extern DECLSPEC const AG_Unit agEnergyPerSubstanceAmountUnits[];
extern DECLSPEC const AG_Unit agMolarHeatCapacityUnits[];
extern DECLSPEC const AG_Unit agLightUnits[];
extern DECLSPEC const AG_Unit agPowerUnits[];
extern DECLSPEC const AG_Unit agEMFUnits[];
extern DECLSPEC const AG_Unit agResistanceUnits[];
extern DECLSPEC const AG_Unit agResistanceTC1Units[];
extern DECLSPEC const AG_Unit agResistanceTC2Units[];
extern DECLSPEC const AG_Unit agCapacitanceUnits[];
extern DECLSPEC const AG_Unit agInductanceUnits[];
extern DECLSPEC const AG_Unit agFrequencyUnits[];
extern DECLSPEC const AG_Unit agPressureUnits[];
extern DECLSPEC const AG_Unit agVacuumUnits[];
extern DECLSPEC const AG_Unit agResistivityUnits[];
extern DECLSPEC const AG_Unit agThermalConductivityUnits[];
extern DECLSPEC const AG_Unit agThermalExpansionUnits[];
extern DECLSPEC const AG_Unit agDensityUnits[];
extern DECLSPEC int AG_UnitIsNonlinear(const char *_Nonnull) _Const_Attribute;
extern DECLSPEC double AG_Unit2Base(double, const AG_Unit *_Nonnull) _Pure_Attribute;
extern DECLSPEC double AG_Base2Unit(double, const AG_Unit *_Nonnull) _Pure_Attribute;
extern DECLSPEC double AG_Unit2Unit(double, const AG_Unit *_Nonnull, const AG_Unit *_Nonnull) _Pure_Attribute;
extern DECLSPEC const char *_Nonnull AG_UnitAbbr(const AG_Unit *_Nonnull) _Pure_Attribute;
extern DECLSPEC const AG_Unit *_Nullable AG_FindUnit(const char *_Nonnull);
extern DECLSPEC const AG_Unit *_Nonnull AG_BestUnit(const AG_Unit[_Nonnull], double);
extern DECLSPEC int AG_UnitFormat(double, const AG_Unit[_Nonnull], char *_Nonnull, AG_Size);
#define AG_Unit2Basef(n, u) ((float)AG_Unit2Base((float)(n), (u)))
#define AG_Base2Unitf(n, u) ((float)AG_Base2Unit((float)(n), (u)))
#define AG_Unit2Unitf(n, u1, u2) ((float)AG_Unit2Unit((float)(n), (u1), (u2)))
__END_DECLS
/* Close generated block */

#include <agar/gui/close.h>
#endif /* _AGAR_WIDGET_UNITS_H_ */
