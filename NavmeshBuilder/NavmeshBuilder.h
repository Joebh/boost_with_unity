#pragma once
#ifndef NAVMESHBUILDER_H
#define NAVMESHBUILDER_H
#include "Interfaces.h"
#include "InputGeom.h"

class NavmeshBuilder
{
public:
	NavmeshBuilder(BuildContext *ctx, InputGeom *geom);
	~NavmeshBuilder();

	bool handleBuild();
private:
	class InputGeom* m_geom;
	class dtNavMesh* m_navMesh;
	class dtNavMeshQuery* m_navQuery;
	class dtCrowd* m_crowd;

	unsigned char m_navMeshDrawFlags;

	float m_cellSize;
	float m_cellHeight;
	float m_agentHeight;
	float m_agentRadius;
	float m_agentMaxClimb;
	float m_agentMaxSlope;
	float m_regionMinSize;
	float m_regionMergeSize;
	float m_edgeMaxLen;
	float m_edgeMaxError;
	float m_vertsPerPoly;
	float m_detailSampleDist;
	float m_detailSampleMaxError;
	int m_partitionType;

	bool m_filterLowHangingObstacles;
	bool m_filterLedgeSpans;
	bool m_filterWalkableLowHeightSpans;

	BuildContext* m_ctx;

	bool m_keepInterResults;
	float m_totalBuildTimeMs;

	unsigned char* m_triareas;
	rcHeightfield* m_solid;
	rcCompactHeightfield* m_chf;
	rcContourSet* m_cset;
	rcPolyMesh* m_pmesh;
	rcConfig m_cfg;
	rcPolyMeshDetail* m_dmesh;


	void cleanup();
	// Explicitly disabled copy constructor and copy assignment operator.
	NavmeshBuilder(const NavmeshBuilder&);
	NavmeshBuilder& operator=(const NavmeshBuilder&);
};

#endif // NAVMESHBUILDER_H
