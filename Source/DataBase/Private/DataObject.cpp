#include "DataObject.h"

UDataObject::UDataObject()
{
	Fields.Init(FDataTableColumnDescription(), 1);
	bUseCustomWidgets = true;
}

