#pragma once
#include "Declare.h"
#include "Initilize.h"

void idle() {
	/* Implement: update spheres and handle collision at boundary*/

	end_t = clock();
	if (end_t - start_t > 1000 / 60) {
		/* Start pushing first block */
		if (stage_Location[0] < 0)
			stage_Location[0] += 0.1;
		else
			stage_Location[0] += 0.02;
		stage.stage1(stage_Location[0]);
		stage_Sphere[0].setCenter(stage.getCenter()[0], stage.getCenter()[1], 0);

		/* Pushing other blocks using previous block */
		for (vector<double>::size_type i = 1; i < stage_Location.size(); i++) {
			if (stage_Location[i] - stage_Location[i - 1] < 1) {
				stage_Location[i] = stage_Location[i - 1] + 0.98;
			}
			else
				break;
			stage.stage1(stage_Location[i]);
			stage_Sphere[i].setCenter(stage.getCenter()[0], stage.getCenter()[1], 0);
		}

		/* Collision handling with shooted sphere */
		for (vector<Sphere>::size_type i = 0; i < shootings.size(); i++) {
			for (vector<Sphere>::size_type j = i + 1; j < shootings.size(); j++) {
				handleCollision(shootings[i], shootings[j]);
				if (isCollisionDetected(shootings[i], shootings[j])) {
					shootings[i].move();
					shootings[j].move();
				}
			}
		}

		/* Erase shooted sphere with a probability */
		vector<Sphere>::size_type i = 0;
		while (i < shootings.size()) {
			shootings[i].move();
			if (shootings[i].getCenter()[0] - shootings[i].getRadius() < -boundaryX || shootings[i].getCenter()[0] + shootings[i].getRadius() > boundaryX) {
				shootings[i].getVelocity()[0] *= -1;
				
				while (shootings[i].getCenter()[0] - shootings[i].getRadius() < -boundaryX || shootings[i].getCenter()[0] + shootings[i].getRadius() > boundaryX)
					shootings[i].move();
				
				if (rand() % 100 < delete_probability) {
					shootings.erase(shootings.begin() + i);
					i -= 1;
				}
			}
			else if (shootings[i].getCenter()[1] - shootings[i].getRadius() < -boundaryY || shootings[i].getCenter()[1] + shootings[i].getRadius() > boundaryY) {
				shootings[i].getVelocity()[1] *= -1;
				
				while (shootings[i].getCenter()[1] - shootings[i].getRadius() < -boundaryY || shootings[i].getCenter()[1] + shootings[i].getRadius() > boundaryY)
					shootings[i].move();
				
				if (rand() % 100 < delete_probability) {
					shootings.erase(shootings.begin() + i);
					i -= 1;
				}
			}
			i++;
		}
		/* Todo: Handle collision with stage_Sphere and shootings */
		
		for (vector<Sphere>::size_type j = 0; j < stage_Sphere.size(); j++) {
			i = 0;
			while (i < shootings.size()) {
				if (isCollisionDetected(shootings[i], stage_Sphere[j])) {
					shootings[i].setVelocity(0, 0, 0);
					pair<Sphere, int> p(shootings[i],j);
					merge.push_back(p);
					merge_prograss.push_back(0);
					shootings.erase(shootings.begin() + i);
					i -= 1;
				}
				i++;
			}
		}

		//while (merge.size()) {
			for (vector<pair<Sphere, int>>::size_type i = 0; i < merge.size(); i++) {
				stage.stage1(stage_Location[merge[i].second]);
				float xs1 = stage.getCenter()[0], ys1 = stage.getCenter()[1];
				stage.stage1(stage_Location[merge[i].second] + 1);
				float xs2 = stage.getCenter()[0], ys2 = stage.getCenter()[1];
				stage.stage1(stage_Location[merge[i].second] + 0.5);
				float xm = stage.getCenter()[0], ym = stage.getCenter()[1];
				switch (merge_prograss[i]) {
				case 0:
					merge[i].first.setCenter(xm + 30 * (ys2 - ys1) / sqrt((xs2 - xs1) * (xs2 - xs1) + (ys2 - ys1) * (ys2 - ys1)), ym - 30 * (xs2 - xs1) / sqrt((xs2 - xs1) * (xs2 - xs1) + (ys2 - ys1) * (ys2 - ys1)), 0);
					//merge_prograss[i] += 1;
					break;
				case 1:
					stage_Location[merge[i].second];

				default:
					break;
				}
				
			}



		//}
		for (vector<Sound>::size_type i = 0; i < sound.size(); i++) {
			sound[i].updatesound();
		}

		start_t = end_t;
		glutPostRedisplay();
	}
}
