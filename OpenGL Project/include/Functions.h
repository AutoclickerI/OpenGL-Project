#pragma once
#include "Declare.h"

bool isCollisionDetected(const Sphere& sph1, const Sphere& sph2) {
	/* Implement: collision detection */
	return sph1.getRadius() + sph2.getRadius() > sph1.getdistance(sph2);
}

void handleCollision(Sphere& sph1, Sphere& sph2) {
	if (isCollisionDetected(sph1, sph2)) {
		/* Implement: collision handling */
		double c1x, c2x, c1y, c2y, v1x, v2x, v1y, v2y, r1, r2;
		c1x = sph1.getCenter()[0]; c1y = sph1.getCenter()[1];
		c2x = sph2.getCenter()[0]; c2y = sph2.getCenter()[1];
		v1x = sph1.getVelocity()[0]; v1y = sph1.getVelocity()[1];
		v2x = sph2.getVelocity()[0]; v2y = sph2.getVelocity()[1];
		r1 = sph1.getRadius(); r2 = sph2.getRadius();

		sph1.getVelocity()[0] = v1x - ((v1x - v2x) * (c1x - c2x) + (v1y - v2y) * (c1y - c2y)) / pow(sph1.getdistance(sph2), 2.0) * (c1x - c2x);
		sph1.getVelocity()[1] = v1y - ((v1x - v2x) * (c1x - c2x) + (v1y - v2y) * (c1y - c2y)) / pow(sph1.getdistance(sph2), 2.0) * (c1y - c2y);
		sph2.getVelocity()[0] = v2x + ((v1x - v2x) * (c1x - c2x) + (v1y - v2y) * (c1y - c2y)) / pow(sph1.getdistance(sph2), 2.0) * (c1x - c2x);
		sph2.getVelocity()[1] = v2y + ((v1x - v2x) * (c1x - c2x) + (v1y - v2y) * (c1y - c2y)) / pow(sph1.getdistance(sph2), 2.0) * (c1y - c2y);
	}
}

void gameoverprocess() {
	mode = GAMEOVER;
	STAGE_NOW = STAGE1;
	sound[STAGEFAILED].playsound();
	for (int i = 0; i < 10; i++) {
		if (score > scoredata[i]) {
			ranking = i;
			scoredata.insert(scoredata.begin() + i, score);
			switch (difficulty) {
			case EASY:
				difficultydata.insert(difficultydata.begin() + i, "EASY");
				break;
			case NORMAL:
				difficultydata.insert(difficultydata.begin() + i, "NORMAL");
				break;
			case HARD:
				difficultydata.insert(difficultydata.begin() + i, "HARD");
				break;
			}
			scoredata.erase(scoredata.begin() + 10);
			difficultydata.erase(difficultydata.begin() + 10);
			scorechange = 1;
			break;
		}
	}
	score = 0;
}