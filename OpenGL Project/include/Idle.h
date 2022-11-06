#pragma once
#include "Declare.h"
#include "Initilize.h"

void idle() {
	/* Implement: update spheres and handle collision at boundary*/

	end_t = clock();
	if (end_t - start_t > 1000 / 60) {
		int factor = 1;
		/* Start pushing first block */
		if (!merge.size()) {
			if (stage_Location[0] < 0)
				factor = 5;
			else
				factor = 1;
			stage_Location[0] += factor * moving_speed;
		}
		stage.stage1(stage_Location[0]);
		stage_Sphere[0].setCenter(stage.getCenter()[0], stage.getCenter()[1], 0);

		/* Pushing other blocks using previous block */
		for (vector<double>::size_type i = 1; i < stage_Location.size(); i++) {
			if (stage_Location[i] - stage_Location[i - 1] < 1)
				stage_Location[i] = stage_Location[i - 1] + 0.98;
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
					pair<int, int> q(j, 0);
					pair<Sphere, pair<int,int>> p(shootings[i],q);
					merge.push_back(p);
					merge_prograss.push_back(0);
					shootings.erase(shootings.begin() + i);
					i -= 1;
				}
				i++;
			}
		}

		//while (merge.size()) {
			i = 0;
			while(i < merge.size()) {
				if (!merge[i].second.second) {
					ccw = 1;
					if (merge[i].second.first - 1 < 0)
						f = stage_Sphere[merge[i].second.first + 1].getdistance(merge[i].first) > 60 * sqrt(2);
					else
						f = stage_Sphere[merge[i].second.first - 1].getdistance(merge[i].first) < 60 * sqrt(2);
				}
				float xs1, xs2, xm, ys1, ys2, ym;
				if (merge[i].second.first >= 0) {
					stage.stage1(stage_Location[merge[i].second.first] - f);
					xs1 = stage.getCenter()[0]; ys1 = stage.getCenter()[1];
					stage.stage1(stage_Location[merge[i].second.first] + 1 - f);
					xs2 = stage.getCenter()[0]; ys2 = stage.getCenter()[1];
					stage.stage1(stage_Location[merge[i].second.first] + 0.5 - f);
					xm = stage.getCenter()[0]; ym = stage.getCenter()[1];
				}
				else {
					stage.stage1(stage_Location[merge[i].second.first+1]-1 - f);
					xs1 = stage.getCenter()[0]; ys1 = stage.getCenter()[1];
					stage.stage1(stage_Location[merge[i].second.first+1] - f);
					xs2 = stage.getCenter()[0]; ys2 = stage.getCenter()[1];
					stage.stage1(stage_Location[merge[i].second.first+1] - 0.5 - f);
					xm = stage.getCenter()[0]; ym = stage.getCenter()[1];
				}
				if (!merge[i].second.second) {
					if (xs1 * ys2 + xs2 * merge[i].first.getCenter()[1] + merge[i].first.getCenter()[0] * ys1 - xs2 * ys1 - merge[i].first.getCenter()[0] * ys2 - xs1 * merge[i].first.getCenter()[1] > 0)
						ccw *= -1;
				}
				/* switch¹® ´ëÃ¼ */
				if (merge_prograss[i] == 0) {
					merge[i].first.setCenter(xm + ccw * 30 * (ys2 - ys1) / sqrt((xs2 - xs1) * (xs2 - xs1) + (ys2 - ys1) * (ys2 - ys1)), ym - ccw * 30 * (xs2 - xs1) / sqrt((xs2 - xs1) * (xs2 - xs1) + (ys2 - ys1) * (ys2 - ys1)), 0);
					merge[i].second.first -= f;
					f = 0;
					merge[i].second.second = 1;
					merge_prograss[i] += 1;
				}
				else if (merge_prograss[i] == merge_step + 1) {
					merge_prograss[i] -= 1;
					if (merge[i].second.first - f >= 0){
						stage_Location.insert(stage_Location.begin() + 1 + merge[i].second.first - f, stage_Location[merge[i].second.first] + 0.5 - f + 0.49 / merge_step * merge_prograss[i]);
						stage_Sphere.insert(stage_Sphere.begin() + 1 + merge[i].second.first - f, merge[i].first);
					}
					else {
						stage_Location.insert(stage_Location.begin() + 1 + merge[i].second.first - f, stage_Location[merge[i].second.first+1] - 1.5 - f + 0.49 / merge_step * merge_prograss[i]);
						stage_Sphere.insert(stage_Sphere.begin() + 1 + merge[i].second.first - f, merge[i].first);
					}
					merge.erase(merge.begin() + i);
					merge_prograss.erase(merge_prograss.begin() + i);
					i--;
				}
				else{
					if (merge[i].second.first - f >= 0 && merge[i].second.first - f < stage_Location.size())
						if(stage_Location[merge[i].second.first - f]< stage_Location[merge[i].second.first - f] + 0.5 - f - 0.49 / merge_step * merge_prograss[i])
							stage_Location[merge[i].second.first - f] -= 0.49 / merge_step;
					if (merge[i].second.first - f >= 0 && merge[i].second.first - f + 1 < stage_Location.size())
						if (stage_Location[merge[i].second.first - f+1] > stage_Location[merge[i].second.first - f] + 0.5 - f + 0.49 / merge_step * merge_prograss[i])
							stage_Location[merge[i].second.first - f + 1] += 0.49 / merge_step;
					if (merge[i].second.first < 0)
						stage_Location[0] += 0.49 / merge_step;
					for (int j = merge[i].second.first - f; j > 0; j--) {
						if (j > 0&&stage_Location[j] - stage_Location[j - 1] < 1)
							stage_Location[j - 1] = stage_Location[j] - 0.98;
						else
							break;
					}
					for (int j = merge[i].second.first - f + 2; j < stage_Location.size(); j++) {
						if (j > 0&&stage_Location[j] - stage_Location[j - 1] < 1)
							stage_Location[j] = stage_Location[j - 1] + 0.98;
						else
							break;
					}
					if(merge[i].second.first - f>=0)
						stage.stage1(stage_Location[merge[i].second.first - f] + 0.5 - f + 0.49 / merge_step * merge_prograss[i]);
					else
						stage.stage1(stage_Location[merge[i].second.first - f + 1] - 0.5 - f - 0.49 / merge_step * merge_prograss[i]);
					xm = stage.getCenter()[0]; ym = stage.getCenter()[1];
					merge[i].first.setCenter(xm + ccw * 30 * (merge_step - merge_prograss[i]) / merge_step * (ys2 - ys1) / sqrt((xs2 - xs1) * (xs2 - xs1) + (ys2 - ys1) * (ys2 - ys1)), ym - ccw * 30 * (merge_step - merge_prograss[i]) / merge_step * (xs2 - xs1) / sqrt((xs2 - xs1) * (xs2 - xs1) + (ys2 - ys1) * (ys2 - ys1)), 0);
					merge_prograss[i] += 1;
					break;
				}
				i++;
			}



		//}
		for (vector<Sound>::size_type i = 0; i < sound.size(); i++) {
			sound[i].updatesound();
		}

		start_t = end_t;
		glutPostRedisplay();
	}
}
