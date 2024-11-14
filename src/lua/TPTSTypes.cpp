#include "TPTSTypes.h"

AnyType::AnyType(ValueType type_, ValueValue value_):
	type(type_),
	value(value_)
{
}

ValueType AnyType::GetType()
{
	return type;
}

AnyType::operator NumberType()
{
	if (type == TypeNumber)
		return NumberType(std::get<int>(value));
	else if (type == TypeFloat)
		return NumberType(int(std::get<float>(value)));
	else
		throw InvalidConversionException(type, TypeNumber);
}

AnyType::operator FloatType()
{
	if (type == TypeNumber)
		return FloatType(float(std::get<int>(value)));
	else if (type == TypeFloat)
		return FloatType(std::get<float>(value));
	else
		throw InvalidConversionException(type, TypeFloat);
}

AnyType::operator StringType()
{
	if(type == TypeNumber)
	{
		return StringType(PTString::Build(((NumberType *)this)->Value()));
	}
	else if(type == TypeString && std::holds_alternative<PTString>(value))
	{
		return StringType(std::get<PTString>(value));
	}
	else if (type == TypePoint && std::holds_alternative<ui::Point>(value))
	{
		ui::Point thisPoint = std::get<ui::Point>(value);
		return StringType(PTString::Build(thisPoint.X, ",", thisPoint.Y));
	}
	else
		throw InvalidConversionException(type, TypeString);

}

AnyType::operator PointType()
{
	if(type == TypePoint)
	{
		return PointType(std::get<ui::Point>(value));
	}
	else if(type == TypeString)
	{
		int x, y;
		if(PTString::Split comma = std::get<PTString>(value).SplitNumber(x))
			if(comma.After().BeginsWith(","))
				if(PTString::Split end = comma.After().Substr(1).SplitNumber(y))
					if(!end.After().size())
						return PointType(x, y);
		throw InvalidConversionException(type, TypePoint);
	}
	else
		throw InvalidConversionException(type, TypePoint);
}

//Number Type

NumberType::NumberType(int number): AnyType(TypeNumber, ValueValue())
{
	value = number;
}

int NumberType::Value()
{
	return std::get<int>(value);
}

//Float Type

FloatType::FloatType(float number): AnyType(TypeFloat, ValueValue())
{
	value = number;
}

float FloatType::Value()
{
	return std::get<float>(value);
}

//PTString type

StringType::StringType(PTString string):	AnyType(TypeString, ValueValue())
{
	value = string;
}

PTString StringType::Value()
{
	return std::get<PTString>(value);
}

//Point type

PointType::PointType(ui::Point point): AnyType(TypePoint, ValueValue())
{
	value = point;
}

PointType::PointType(int pointX, int pointY): AnyType(TypePoint, ValueValue())
{
	value = ui::Point(pointX, pointY);
}

ui::Point PointType::Value()
{
	return std::get<ui::Point>(value);
}
