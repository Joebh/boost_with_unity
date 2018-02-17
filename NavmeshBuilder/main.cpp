#include "stdafx.h"
#include <iostream>
#include "NavmeshBuilder.h"
#include "Interfaces.h"
#include "InputGeom.h"

int main()
{
	BuildContext ctx;
	InputGeom geom;

	NavmeshBuilder builder(&ctx, &geom);

	geom.load(&ctx, "D:/recastnavigation/RecastDemo/Bin/Meshes/terrain.obj");
	
	ctx.dumpLog("");
	builder.handleBuild();
    return 0;
}

