#pragma once
#include "Declare.h"
#include "Initilize.h"

void idle() {
	/* Implement: update spheres and handle collision at boundary*/
	end_t = clock();
	if (end_t - start_t > 1000 / Frame) {
		int factor = 1;
		vector<Sphere>::size_type i;
		if (!pause) {
			switch (mode) {
			case MOVING:
				/* Start pushing first block */
				if (!merge.size()) {
					if (!stage_Location.size()) {
						mode = CLEAR;
						STAGE_NOW = static_cast<STAGE>(STAGE_NOW % 4 + 1);
						sound[STAGECLEAR].playsound();
						break;
					}
					switch (STAGE_NOW) {
					case STAGE1:
					case STAGE2:
						if (stage_Location.back() > 44) gameoverprocess();
						break;
					case STAGE3:
						if (stage_Location.back() > 70) gameoverprocess();
						break;
					case STAGE4:
						if (stage_Location.back() > 55)	gameoverprocess();
						break;
					case STAGE5:
						if (stage_Location.back() > 68) gameoverprocess();
						break;
					default:
						break;
					}
					if (end_t - item_t > 5000 && velocityrevert == 0 && item == 0) {
						moving_speed *= 10;
						velocityrevert = 1;
					}
					if (stage_Location[0] < 0)
						factor = 5;
					else
						factor = 1;
					stage_Location[0] += factor * moving_speed;
				}
				stage.setPos(stage_Location[0], STAGE_NOW);
				stage_Sphere[0].setCenter(stage.getCenter()[0], stage.getCenter()[1], 0);

				/* Pushing other blocks using previous block */
				for (vector<double>::size_type i = 1; i < stage_Location.size(); i++) {
					if (stage_Location[i] - stage_Location[i - 1] < 0.98)
						stage_Location[i] = stage_Location[i - 1] + 0.98;
					stage.setPos(stage_Location[i], STAGE_NOW);
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
							merge.push_back(pair<Sphere, pair<int, int>>(shootings[i], pair<int, int>(j, 0)));
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
						stage.setPos(stage_Location[merge[0].second.first] + 1, STAGE_NOW);
						f = pow(merge[0].first.getCenter()[0] - stage.getCenter()[0], 2.0) + pow(merge[0].first.getCenter()[1] - stage.getCenter()[1], 2.0) > 7057.44;
					}
					float xs1, xs2, xm, ys1, ys2, ym;
					//backward pass
					if (f) {
						stage.setPos(stage_Location[merge[0].second.first] - 1, STAGE_NOW);
						xs1 = stage.getCenter()[0]; ys1 = stage.getCenter()[1];
						stage.setPos(stage_Location[merge[0].second.first], STAGE_NOW);
						xs2 = stage.getCenter()[0]; ys2 = stage.getCenter()[1];
						stage.setPos(stage_Location[merge[0].second.first] - 0.49, STAGE_NOW);
						xm = stage.getCenter()[0]; ym = stage.getCenter()[1];

						if (!merge[0].second.second) {
							if (xs1 * ys2 + xs2 * merge[0].first.getCenter()[1] + merge[0].first.getCenter()[0] * ys1 - xs2 * ys1 - merge[0].first.getCenter()[0] * ys2 - xs1 * merge[0].first.getCenter()[1] > 0)
								ccw *= -1;
						}
					}
					//forward pass
					else
					{
						stage.setPos(stage_Location[merge[0].second.first], STAGE_NOW);
						xs1 = stage.getCenter()[0]; ys1 = stage.getCenter()[1];
						stage.setPos(stage_Location[merge[0].second.first] + 1, STAGE_NOW);
						xs2 = stage.getCenter()[0]; ys2 = stage.getCenter()[1];
						stage.setPos(stage_Location[merge[0].second.first] + 0.49, STAGE_NOW);
						xm = stage.getCenter()[0]; ym = stage.getCenter()[1];

						if (!merge[0].second.second) {
							if (xs1 * ys2 + xs2 * merge[0].first.getCenter()[1] + merge[0].first.getCenter()[0] * ys1 - xs2 * ys1 - merge[0].first.getCenter()[0] * ys2 - xs1 * merge[0].first.getCenter()[1] > 0)
								ccw *= -1;
						}
					}
					/* switchπÆ ¥Î√º */
					if (merge_prograss[0] == 0) {
						merge[0].first.setCenter(xm + ccw * 30 * (ys2 - ys1) / sqrt((xs2 - xs1) * (xs2 - xs1) + (ys2 - ys1) * (ys2 - ys1)), ym - ccw * 30 * (xs2 - xs1) / sqrt((xs2 - xs1) * (xs2 - xs1) + (ys2 - ys1) * (ys2 - ys1)), 0);
						merge[0].second.second = 1;
						merge_prograss[0] += 1;

						//Fixing erasing effect

						boom_mtl = merge[0].first.getnum();
						boom_pos = merge[0].second.first;
						boom_pos_end = boom_pos;
						stage_Location.insert(stage_Location.begin() + 1 - f + merge[0].second.first, stage_Location[merge[0].second.first] + 0.49 - 0.98 * f + 0.49 / (Frame/6) * merge_prograss[0]);
						stage_Sphere.insert(stage_Sphere.begin() + 1 - f + merge[0].second.first, merge[0].first);

						//backward pass
						if (f) {
							if (0 < boom_pos && boom_mtl == stage_Sphere[boom_pos - 1].getnum() && stage_Location[boom_pos] - stage_Location[boom_pos - 1] < 0.9801)
								boom_pos--;
							while (0 < boom_pos && boom_mtl == stage_Sphere[boom_pos - 1].getnum() && stage_Location[boom_pos] - stage_Location[boom_pos - 1] < 0.9801)
								boom_pos -= 1;
							while (boom_pos_end + 1 < (int)stage_Sphere.size() && boom_mtl == stage_Sphere[boom_pos_end + 1].getnum() && stage_Location[boom_pos_end + 1] - stage_Location[boom_pos_end] < 0.9801)
								boom_pos_end += 1;
							if (boom_pos_end - boom_pos > 1) {
								mode = BOOM;
								boom_stack = 0;
								merge.erase(merge.begin());
								merge_prograss.erase(merge_prograss.begin());
								break;
							}
						}

						//forward pass
						else {
							if (boom_pos + 1 < (int)stage_Sphere.size() && boom_mtl == stage_Sphere[boom_pos + 1].getnum() && stage_Location[boom_pos + 1] - stage_Location[boom_pos] < 0.9801)
								boom_pos_end++;
							while (0 < boom_pos && boom_mtl == stage_Sphere[boom_pos].getnum() && stage_Location[boom_pos] - stage_Location[boom_pos - 1] < 0.9801)
								boom_pos -= 1;
							while (boom_pos_end + 1 < (int)stage_Sphere.size() && boom_mtl == stage_Sphere[boom_pos_end + 1].getnum() && stage_Location[boom_pos_end + 1] - stage_Location[boom_pos_end] < 0.9801)
								boom_pos_end += 1;
							if ((boom_pos == 0 || stage_Location[boom_pos] - stage_Location[boom_pos - 1] > 1.46) && boom_mtl == stage_Sphere[boom_pos].getnum() && boom_pos_end - boom_pos > 1) {
								mode = BOOM;
								boom_stack = 0;
								merge.erase(merge.begin());
								merge_prograss.erase(merge_prograss.begin());
								break;
							}

							else if (boom_pos_end - boom_pos > 2) {
								mode = BOOM;
								boom_stack = 0;
								merge.erase(merge.begin());
								merge_prograss.erase(merge_prograss.begin()); \
									boom_pos++;
								break;
							}
						}
						stage_Location.erase(stage_Location.begin() + 1 - f + merge[0].second.first);
						stage_Sphere.erase(stage_Sphere.begin() + 1 - f + merge[0].second.first);

					}


					/* merge */
					else if (merge_prograss[0] == (Frame/6) + 1) {
						merge_prograss[0] -= 1;
						//backward pass
						stage_Location.insert(stage_Location.begin() + 1 + merge[0].second.first - f, stage_Location[merge[0].second.first] + 0.49 - 1.96 * f + 0.49 / (Frame/6) * merge_prograss[0]);
						stage_Sphere.insert(stage_Sphere.begin() + 1 + merge[0].second.first - f, merge[0].first);
						boom_pos = 1 + merge[0].second.first - f;
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
							stage_Location[merge[0].second.first] += 0.49 / (Frame/6);
							if (merge[0].second.first - 1 >= 0)
								if (stage_Location[merge[0].second.first - 1] > stage_Location[merge[0].second.first] - 0.98 - 0.98 / (Frame/6) * merge_prograss[0])
									stage_Location[merge[0].second.first - 1] = stage_Location[merge[0].second.first] - 0.98 - 0.98 / (Frame/6) * merge_prograss[0];
							if (merge[0].second.first < 0)
								stage_Location[0] += 0.49 / (Frame/6);
							for (int j = merge[0].second.first - 1; j > 0; j--) {
								if (j > 0 && stage_Location[j] - stage_Location[j - 1] < 0.98)
									stage_Location[j - 1] = stage_Location[j] - 0.98;
								else
									break;
							}
							for (int j = merge[0].second.first + 1; j < (int)stage_Location.size(); j++) {
								if (j > 0 && stage_Location[j] - stage_Location[j - 1] < 0.98)
									stage_Location[j] = stage_Location[j - 1] + 0.98;
								else
									break;
							}
							stage.setPos(stage_Location[merge[0].second.first] - 0.49 - 0.49 / (Frame/6) * merge_prograss[0], STAGE_NOW);
						}
						//forward pass
						else {
							stage_Location[merge[0].second.first] -= 0.49 / (Frame/6);
							if (merge[0].second.first + 1 < (int)stage_Location.size())
								if (stage_Location[merge[0].second.first + 1] < stage_Location[merge[0].second.first] + 0.98 + 0.98 / (Frame/6) * merge_prograss[0])
									stage_Location[merge[0].second.first + 1] = stage_Location[merge[0].second.first] + 0.98 + 0.98 / (Frame/6) * merge_prograss[0];
							for (int j = merge[0].second.first; j > 0; j--) {
								if (j > 0 && stage_Location[j] - stage_Location[j - 1] < 0.98)
									stage_Location[j - 1] = stage_Location[j] - 0.98;
								else
									break;
							}
							for (int j = merge[0].second.first + 2; j < (int)stage_Location.size(); j++) {
								if (j > 0 && stage_Location[j] - stage_Location[j - 1] < 0.98)
									stage_Location[j] = stage_Location[j - 1] + 0.98;
								else
									break;
							}
							stage.setPos(stage_Location[merge[0].second.first] + 0.49 + 0.49 / (Frame/6) * merge_prograss[0], STAGE_NOW);
						}
						xm = stage.getCenter()[0]; ym = stage.getCenter()[1];
						merge[0].first.setCenter(xm + ccw * 30 * ((Frame/6) - merge_prograss[0]) / (Frame/6) * (ys2 - ys1) / sqrt((xs2 - xs1) * (xs2 - xs1) + (ys2 - ys1) * (ys2 - ys1)), ym - ccw * 30 * ((Frame/6) - merge_prograss[0]) / (Frame/6) * (xs2 - xs1) / sqrt((xs2 - xs1) * (xs2 - xs1) + (ys2 - ys1) * (ys2 - ys1)), 0);
						merge_prograss[0] += 1;
					}
				}
				break;
			case BOOM:
				if (boom_pos_end - boom_pos > 1) {
					boom_stack += 1;
					sound[BOOMSOUND].playsound();
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
				while (boom_pos_end < (int)stage_Sphere.size() && boom_mtl == stage_Sphere[boom_pos_end].getnum())
					boom_pos_end += 1;
				if (boom_pos_end - boom_pos > 2 && boom_pos_end_end < boom_pos_end - 1) {
					boom_stack += 1;
					boom_pos_end_end = boom_pos_end;
					while (boom_pos_end_end < (int)stage_Sphere.size())
						if (stage_Location[boom_pos_end_end - 1] + 0.9801 > stage_Location[boom_pos_end_end])
							boom_pos_end_end++;
						else
							break;
					mode = CHAIN_DRAG;
				}
				else
					mode = MOVING;
				break;
			case DRAG:
				if (boom_stack > (Frame/6) * 4) {
					while (boom_pos_end - boom_pos + 1) {
						stage_Sphere.erase(stage_Sphere.begin() + boom_pos);
						stage_Location.erase(stage_Location.begin() + boom_pos);
						boom_pos_end--;
						score += (550 * difficulty * difficulty - 150 * difficulty + 100) * (level + 1);
					}
					boom_stack = 0;
					boom_pos -= 1;
					mode = CHAIN_BOOM;
					while (merge.size()) {
						shootings.push_back(merge[0].first);
						merge.erase(merge.begin());
						merge_prograss.erase(merge_prograss.begin());
					}
				}
				else {
					if ((2 * boom_stack - 1) / (Frame/6) % 2)
						for (int k = boom_pos; k <= boom_pos_end; k++) {
							stage_Sphere[k].showSphere(false);
						}
					else
						for (int k = boom_pos; k <= boom_pos_end; k++) {
							stage_Sphere[k].showSphere(true);
						}
					boom_stack += 1;
				}
				break;
			case CHAIN_DRAG:
				if (stage_Location[boom_pos] + 0.98 * (boom_pos_end_end - 1 - boom_pos) + 0.001 < stage_Location[boom_pos_end_end - 1]) {
					for (int step = 0; step < 20; step++) {
						if (stage_Location[boom_pos] + 0.98 * (boom_pos_end_end - 1 - boom_pos) + 0.001 < stage_Location[boom_pos_end_end - 1])
							stage_Location[boom_pos_end_end - 1] -= moving_speed / 2.0f;
						for (int l = boom_pos_end_end - 1; l > boom_pos; l--) {
							if (stage_Location[l] - stage_Location[l - 1] < 0.98)
								stage_Location[l - 1] = stage_Location[l] - 0.98;
							else
								break;
						}
					}
					for (vector<double>::size_type i = 1; i < stage_Location.size(); i++) {
						stage.setPos(stage_Location[i], STAGE_NOW);
						stage_Sphere[i].setCenter(stage.getCenter()[0], stage.getCenter()[1], 0);
					}
				}
				else {
					if (boom_stack) {
						if (boom_stack == 1)
							sound[BOOMSOUND].playsound();
						if (boom_stack > (Frame/6) * 4) {
							int cnt = 0;
							while (boom_pos < (int)stage_Sphere.size() && boom_mtl == stage_Sphere[boom_pos].getnum()) {
								stage_Sphere.erase(stage_Sphere.begin() + boom_pos);
								stage_Location.erase(stage_Location.begin() + boom_pos);
								cnt++;
							}
							score *= cnt - 2 + difficulty;
							boom_stack = 0;
							boom_pos -= 1;
							mode = CHAIN_BOOM;
						}
						else {
							if ((2 * boom_stack - 1) / (Frame/6) % 2)
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
						mode = CHAIN_BOOM;
				}
				break;

			case GAMEOVER:
				if (scorechange == 1)
					mode = SCORESAVE;
				break;
			case SCORESAVE:
				if (scorechange == 1) {
					ofstream oscore("config.ini");
					if (oscore.is_open()) {
						oscore << trash << " ";
						for (int i = 0; i < 10; i++) {
							oscore << playername[i] << " " << scoredata[i] << " " << difficultydata[i] << " ";
						}
						oscore << Frame << " " << manual << " " << theme << endl;
						scorechange = 0;
						oscore.close();
					}
				}
				break;
			default:
				break;
			}
		}
		for (vector<Sound>::size_type i = 0; i < sound.size(); i++) {
			sound[i].updatesound();
		}
		start_t = end_t;
		glutPostRedisplay();
	}
	if (score > 999999999)
		score = 999999999;
}