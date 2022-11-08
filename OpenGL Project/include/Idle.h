#pragma once
#include "Declare.h"
#include "Initilize.h"

void idle() {
	/* Implement: update spheres and handle collision at boundary*/

	end_t = clock();
	if (end_t - start_t > 1000 / Frame) {
		int factor = 1;
		vector<Sphere>::size_type i;
		switch (mode) {
		case MOVING:
			/* Start pushing first block */
			if (!merge.size()) {
				if (!stage_Location.size()) {
					mode = CLEAR;
					break;
				}
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
			i = 0;
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
						pair<int, int> q(j, 0);
						pair<Sphere, pair<int, int>> p(shootings[i], q);
						merge.push_back(p);
						merge_prograss.push_back(0);
						shootings.erase(shootings.begin() + i);
						i -= 1;
					}
					i++;
				}
			}


			if (merge.size()) {
				if (!merge[0].second.second) {
					ccw = 1;
					stage.stage1(stage_Location[merge[0].second.first] + 1);
					f = pow(merge[0].first.getCenter()[0] - stage.getCenter()[0], 2.0) + pow(merge[0].first.getCenter()[1] - stage.getCenter()[1], 2.0) > 7057.44;
				}
				float xs1, xs2, xm, ys1, ys2, ym;
				//backward pass
				if (f) {
					stage.stage1(stage_Location[merge[0].second.first] - 1);
					xs1 = stage.getCenter()[0]; ys1 = stage.getCenter()[1];
					stage.stage1(stage_Location[merge[0].second.first]);
					xs2 = stage.getCenter()[0]; ys2 = stage.getCenter()[1];
					stage.stage1(stage_Location[merge[0].second.first] - 0.5);
					xm = stage.getCenter()[0]; ym = stage.getCenter()[1];

					if (!merge[0].second.second) {
						if (xs1 * ys2 + xs2 * merge[0].first.getCenter()[1] + merge[0].first.getCenter()[0] * ys1 - xs2 * ys1 - merge[0].first.getCenter()[0] * ys2 - xs1 * merge[0].first.getCenter()[1] > 0)
							ccw *= -1;
					}
				}
				//forward pass
				else
				{
					stage.stage1(stage_Location[merge[0].second.first]);
					xs1 = stage.getCenter()[0]; ys1 = stage.getCenter()[1];
					stage.stage1(stage_Location[merge[0].second.first] + 1);
					xs2 = stage.getCenter()[0]; ys2 = stage.getCenter()[1];
					stage.stage1(stage_Location[merge[0].second.first] + 0.5);
					xm = stage.getCenter()[0]; ym = stage.getCenter()[1];

					if (!merge[0].second.second) {
						if (xs1 * ys2 + xs2 * merge[0].first.getCenter()[1] + merge[0].first.getCenter()[0] * ys1 - xs2 * ys1 - merge[0].first.getCenter()[0] * ys2 - xs1 * merge[0].first.getCenter()[1] > 0)
							ccw *= -1;
					}
				}
				/* switch¹® ´ëÃ¼ */
				if (merge_prograss[0] == 0) {
					merge[0].first.setCenter(xm + ccw * 30 * (ys2 - ys1) / sqrt((xs2 - xs1) * (xs2 - xs1) + (ys2 - ys1) * (ys2 - ys1)), ym - ccw * 30 * (xs2 - xs1) / sqrt((xs2 - xs1) * (xs2 - xs1) + (ys2 - ys1) * (ys2 - ys1)), 0);
					merge[0].second.second = 1;
					merge_prograss[0] += 1;
				}

				/* merge */
				else if (merge_prograss[0] == merge_step + 1) {
					merge_prograss[0] -= 1;
					//backward pass
					if (f) {
						stage_Location.insert(stage_Location.begin() + merge[0].second.first, stage_Location[merge[0].second.first] - 1.5 + 0.49 / merge_step * merge_prograss[0]);
						stage_Sphere.insert(stage_Sphere.begin() + merge[0].second.first, merge[0].first);
						boom_pos = merge[0].second.first;
					}
					//forward pass
					else {
						stage_Location.insert(stage_Location.begin() + 1 + merge[0].second.first, stage_Location[merge[0].second.first] + 0.5 + 0.49 / merge_step * merge_prograss[0]);
						stage_Sphere.insert(stage_Sphere.begin() + 1 + merge[0].second.first, merge[0].first);
						boom_pos = 1 + merge[0].second.first;
					}
					mode = BOOM;
					boom_stack = 0;
					merge.erase(merge.begin());
					merge_prograss.erase(merge_prograss.begin());
					while (merge.size()) {
						shootings.push_back(merge[0].first);
						merge.erase(merge.begin());
						merge_prograss.erase(merge_prograss.begin());
					}

				}

				/* reposition */
				else {
					//backward pass
					if (f) {
						stage_Location[merge[0].second.first] += 0.49 / merge_step;
						if (merge[0].second.first - 1 >= 0)
							if (stage_Location[merge[0].second.first - 1] > stage_Location[merge[0].second.first] - 0.98 - 0.98 / merge_step * merge_prograss[0])
								stage_Location[merge[0].second.first - 1] = stage_Location[merge[0].second.first] - 0.98 - 0.98 / merge_step * merge_prograss[0];
						if (merge[0].second.first < 0)
							stage_Location[0] += 0.49 / merge_step;
						for (int j = merge[0].second.first - 1; j > 0; j--) {
							if (j > 0 && stage_Location[j] - stage_Location[j - 1] < 1)
								stage_Location[j - 1] = stage_Location[j] - 0.98;
							else
								break;
						}
						for (int j = merge[0].second.first + 1; j < stage_Location.size(); j++) {
							if (j > 0 && stage_Location[j] - stage_Location[j - 1] < 1)
								stage_Location[j] = stage_Location[j - 1] + 0.98;
							else
								break;
						}
						stage.stage1(stage_Location[merge[0].second.first] - 0.49 - 0.49 / merge_step * merge_prograss[0]);
					}
					//forward pass
					else {
						stage_Location[merge[0].second.first] -= 0.49 / merge_step;
						if (merge[0].second.first + 1 < stage_Location.size())
							if (stage_Location[merge[0].second.first + 1] < stage_Location[merge[0].second.first] + 0.98 + 0.98 / merge_step * merge_prograss[0])
								stage_Location[merge[0].second.first + 1] = stage_Location[merge[0].second.first] + 0.98 + 0.98 / merge_step * merge_prograss[0];
						for (int j = merge[0].second.first; j > 0; j--) {
							if (j > 0 && stage_Location[j] - stage_Location[j - 1] < 1)
								stage_Location[j - 1] = stage_Location[j] - 0.98;
							else
								break;
						}
						for (int j = merge[0].second.first + 2; j < stage_Location.size(); j++) {
							if (j > 0 && stage_Location[j] - stage_Location[j - 1] < 1)
								stage_Location[j] = stage_Location[j - 1] + 0.98;
							else
								break;
						}
						stage.stage1(stage_Location[merge[0].second.first] + 0.49 + 0.49 / merge_step * merge_prograss[0]);
					}
					xm = stage.getCenter()[0]; ym = stage.getCenter()[1];
					merge[0].first.setCenter(xm + ccw * 30 * (merge_step - merge_prograss[0]) / merge_step * (ys2 - ys1) / sqrt((xs2 - xs1) * (xs2 - xs1) + (ys2 - ys1) * (ys2 - ys1)), ym - ccw * 30 * (merge_step - merge_prograss[0]) / merge_step * (xs2 - xs1) / sqrt((xs2 - xs1) * (xs2 - xs1) + (ys2 - ys1) * (ys2 - ys1)), 0);
					merge_prograss[0] += 1;
				}
			}
			break;
		case BOOM:
			boom_pos_end = boom_pos;
			boom_mtl = stage_Sphere[boom_pos].getnum();
			while (0 < boom_pos && boom_mtl == stage_Sphere[boom_pos - 1].getnum())
				boom_pos -= 1;
			while (boom_pos_end < stage_Sphere.size() && boom_mtl == stage_Sphere[boom_pos_end].getnum())
				boom_pos_end += 1;
			if (boom_pos_end - boom_pos > 2) {
				boom_stack += 1;
				boom_pos_end_end = boom_pos_end;
				while (boom_pos_end_end < stage_Sphere.size())
					if (stage_Location[boom_pos_end_end - 1] + 0.9801 > stage_Location[boom_pos_end_end])
						boom_pos_end_end++;
					else
						break;
				mode = DRAG;
			}
			else
				mode = MOVING;
			break;
		case CHAIN_BOOM:
			boom_pos_end = boom_pos_end_end = boom_pos;
			if (boom_pos < 0) {
				mode = MOVING;
				break;
			}
			boom_mtl = stage_Sphere[boom_pos].getnum();
			while (0 < boom_pos && boom_mtl == stage_Sphere[boom_pos - 1].getnum())
				boom_pos -= 1;
			while (boom_pos_end < stage_Sphere.size() && boom_mtl == stage_Sphere[boom_pos_end].getnum())
				boom_pos_end += 1;
			if (boom_pos_end - boom_pos > 2 && boom_pos_end_end < boom_pos_end - 1) {
				boom_stack += 1;
				boom_pos_end_end = boom_pos_end;
				while (boom_pos_end_end < stage_Sphere.size())
					if (stage_Location[boom_pos_end_end - 1] + 0.9801 > stage_Location[boom_pos_end_end])
						boom_pos_end_end++;
					else
						break;
				mode = DRAG;
			}
			else
				mode = MOVING;
			break;
		case DRAG:
			if (stage_Location[boom_pos] + 0.98 * (boom_pos_end_end - 1 - boom_pos) + 0.001 < stage_Location[boom_pos_end_end - 1]) {
				for (int step=0; step < 20; step++) {
					if (stage_Location[boom_pos] + 0.98 * (boom_pos_end_end - 1 - boom_pos) + 0.001 < stage_Location[boom_pos_end_end - 1])
						stage_Location[boom_pos_end_end - 1] -= moving_speed/2.0f;
					for (int l = boom_pos_end_end - 1; l > boom_pos; l--) {
						if (stage_Location[l] - stage_Location[l - 1] < 0.98)
							stage_Location[l - 1] = stage_Location[l] - 0.98;
						else
							break;
					}
				}
				for (vector<double>::size_type i = 1; i < stage_Location.size(); i++) {
					stage.stage1(stage_Location[i]);
					stage_Sphere[i].setCenter(stage.getCenter()[0], stage.getCenter()[1], 0);
				}
			}
			else {
				if (boom_stack) {
					if (boom_stack > merge_step * 4) {
						while (boom_pos < stage_Sphere.size() && boom_mtl == stage_Sphere[boom_pos].getnum()) {
							stage_Sphere.erase(stage_Sphere.begin() + boom_pos);
							stage_Location.erase(stage_Location.begin() + boom_pos);
						}
						boom_stack = 0;
						boom_pos -= 1;
						mode = CHAIN_BOOM;
					}
					else {
						if ((2 * boom_stack - 1) / merge_step % 2)
							for (int k = boom_pos; k < boom_pos_end; k++) {
								stage_Sphere[k].showSphere(false);
							}
						else
							for (int k = boom_pos; k < boom_pos_end; k++) {
								stage_Sphere[k].showSphere(true);
							}
						boom_stack += 1;
					}
				}
				else
					mode = BOOM;
			}
			break;
		case CLEAR:
			break;
		default:
			break;
		}

		for (vector<Sound>::size_type i = 0; i < sound.size(); i++) {
			sound[i].updatesound();
		}

		start_t = end_t;
		glutPostRedisplay();
	}
}