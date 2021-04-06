#pragma once
#include "Renderer.h"
#include "Model.h";
#include "ModelInfo.h"

namespace Scenes {

	struct Prop {
		Model* m;
		glm::mat4 model;

	};

	enum Scene {
		DINING_TABLE,
		GODZILLA_VS_KINGKONG,
		LEAP_OF_FAITH
	};

	const char* sceneNames[] = {
		"DINING TABLE",
		"GODZILLA VS KINGKONG",
		"LEAP OF FAITH"
	};

	std::vector<Scene> sceneEnums = {
		DINING_TABLE,
		GODZILLA_VS_KINGKONG,
		LEAP_OF_FAITH
	};

	const int count = 3;
	const std::vector<float> cube_positions = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	VertexArray* cube;

	std::vector<Prop> props;

	void selectScene(Scene s)
	{
		props.clear();
		glm::mat4 model;
		switch (s)
		{
		case Scenes::DINING_TABLE:
		{
			glm::vec3 scaleGrass(0.048f, 0.014f, 0.024f);
			glm::vec3 translateGrass(0.0f, 0.0f, -2.582);
			Model* tree = new Model(ModelInfo::getPath(ModelInfo::TREE));
			Model* grass = new Model(ModelInfo::getPath(ModelInfo::GRASS));
			Model* teapot = new Model(ModelInfo::getPath(ModelInfo::TEAPOT));
			model = glm::translate(glm::mat4(1.0f), glm::vec3(-4, 0, -2));
			model = glm::scale(model, glm::vec3(0.1));
			props.push_back({ tree,model });
			model = glm::translate(glm::mat4(1.0f), translateGrass);
			model = glm::scale(model, scaleGrass);
			props.push_back({ grass,model });
			model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,1.0f + 0.25,0.0f));
			model = glm::scale(model, glm::vec3(0.02f));
			props.push_back({ teapot , model });


			cube = new VertexArray();
			VertexBufferLayout* layout = new VertexBufferLayout();
			layout->push<float>(3);
			layout->push<float>(3);
			VertexBuffer* VBO_cube = new VertexBuffer(cube_positions.data(), cube_positions.size() * sizeof(float));
			cube->addBuffer(*VBO_cube, *layout);
		}

			break;
		case Scenes::GODZILLA_VS_KINGKONG:
		{
			model = glm::translate(glm::mat4(1.0f), glm::vec3(-1, 0, 0));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
			model = glm::scale(model, glm::vec3(0.025));
			Model* godzilla = new Model(ModelInfo::getPath(ModelInfo::GODZILLA));
			props.push_back({ godzilla,model });
			model = glm::translate(glm::mat4(1.0f), glm::vec3(1, -0.5, 0));
			model = glm::rotate(model, glm::radians(-54.0f), glm::vec3(0, 1, 0));
			model = glm::scale(model, glm::vec3(0.6));
			Model* kingkong = new Model(ModelInfo::getPath(ModelInfo::KINGKONG));
			props.push_back({ kingkong,model });
		}

			break;
		case Scenes::LEAP_OF_FAITH:
		{
			Model* altair = new Model(ModelInfo::getPath(ModelInfo::ALTAIR));
			Model* castle = new Model(ModelInfo::getPath(ModelInfo::CASTLE));
			model = glm::scale(glm::mat4(1.0f), glm::vec3(0.02f));
			props.push_back({ castle , model });
			model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 12.05f, 0.0f));
			model = glm::scale(model, glm::vec3(0.01 , 0.01 , 0.01));
			props.push_back({ altair , model });
		}

			break;
		default:
			break;
		}
		return;
	}

	void drawScene(Scene s, Shader* shaderObject, Shader* shaderModel)
	{
		switch (s)
		{
		case Scenes::DINING_TABLE:
		{
			float displaceX = 1.5;
			float displaceZ = 0.881;
			cube->bind();
			float tableWidth = 2.0;
			float tableLength = 3.236;
			float tableThickness = 0.122;
			float tableLegLength = 1.0;
			float restHeight = 0.0;

			glm::mat4 tableTop;
			glm::mat4 tableLeg[4];
			glm::mat4 backRest;

			tableTop = glm::mat4(1.0f); tableTop = glm::translate(tableTop, glm::vec3(0.0, tableLegLength, 0.0)); tableTop = glm::scale(tableTop, glm::vec3(tableLength, tableThickness, tableWidth));
			tableLeg[0] = glm::mat4(1.0f); tableLeg[0] = glm::translate(tableLeg[0], glm::vec3(tableLength / 2 - tableThickness / 2, tableLegLength / 2, -(tableWidth / 2 - tableThickness / 2))); tableLeg[0] = glm::scale(tableLeg[0], glm::vec3(tableThickness, tableLegLength, tableThickness));
			tableLeg[1] = glm::mat4(1.0f); tableLeg[1] = glm::translate(tableLeg[1], glm::vec3(-(tableLength / 2 - tableThickness / 2), tableLegLength / 2, -(tableWidth / 2 - tableThickness / 2))); tableLeg[1] = glm::scale(tableLeg[1], glm::vec3(tableThickness, tableLegLength, tableThickness));
			tableLeg[2] = glm::mat4(1.0f); tableLeg[2] = glm::translate(tableLeg[2], glm::vec3(-(tableLength / 2 - tableThickness / 2), tableLegLength / 2, tableWidth / 2 - tableThickness / 2)); tableLeg[2] = glm::scale(tableLeg[2], glm::vec3(tableThickness, tableLegLength, tableThickness));
			tableLeg[3] = glm::mat4(1.0f); tableLeg[3] = glm::translate(tableLeg[3], glm::vec3(tableLength / 2 - tableThickness / 2, tableLegLength / 2, tableWidth / 2 - tableThickness / 2)); tableLeg[3] = glm::scale(tableLeg[3], glm::vec3(tableThickness, tableLegLength, tableThickness));
			backRest = glm::mat4(1.0f); backRest = glm::translate(backRest, glm::vec3(tableLength / 2 - tableThickness / 2, tableLegLength + restHeight / 2, 0));; backRest = glm::scale(backRest, glm::vec3(tableThickness, restHeight, tableWidth));
			shaderObject->bind();
			//DINING TABLE

				shaderObject->setUniformMat4f("model", tableTop);
				GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
				shaderObject->setUniformMat4f("model", tableLeg[0]);
				GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
				shaderObject->setUniformMat4f("model", tableLeg[1]);
				GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
				shaderObject->setUniformMat4f("model", tableLeg[2]);
				GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
				shaderObject->setUniformMat4f("model", tableLeg[3]);
				GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
				shaderObject->setUniformMat4f("model", backRest);
				GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));

			tableWidth = 1.0;
			tableLength = 1.0;
			tableThickness = 0.122;
			tableLegLength = 0.7;
			restHeight = 1.0;

			tableTop = glm::mat4(1.0f); tableTop = glm::translate(tableTop, glm::vec3(0.0, tableLegLength, 0.0)); tableTop = glm::scale(tableTop, glm::vec3(tableLength, tableThickness, tableWidth));
			tableLeg[0] = glm::mat4(1.0f); tableLeg[0] = glm::translate(tableLeg[0], glm::vec3(tableLength / 2 - tableThickness / 2, tableLegLength / 2, -(tableWidth / 2 - tableThickness / 2))); tableLeg[0] = glm::scale(tableLeg[0], glm::vec3(tableThickness, tableLegLength, tableThickness));
			tableLeg[1] = glm::mat4(1.0f); tableLeg[1] = glm::translate(tableLeg[1], glm::vec3(-(tableLength / 2 - tableThickness / 2), tableLegLength / 2, -(tableWidth / 2 - tableThickness / 2))); tableLeg[1] = glm::scale(tableLeg[1], glm::vec3(tableThickness, tableLegLength, tableThickness));
			tableLeg[2] = glm::mat4(1.0f); tableLeg[2] = glm::translate(tableLeg[2], glm::vec3(-(tableLength / 2 - tableThickness / 2), tableLegLength / 2, tableWidth / 2 - tableThickness / 2)); tableLeg[2] = glm::scale(tableLeg[2], glm::vec3(tableThickness, tableLegLength, tableThickness));
			tableLeg[3] = glm::mat4(1.0f); tableLeg[3] = glm::translate(tableLeg[3], glm::vec3(tableLength / 2 - tableThickness / 2, tableLegLength / 2, tableWidth / 2 - tableThickness / 2)); tableLeg[3] = glm::scale(tableLeg[3], glm::vec3(tableThickness, tableLegLength, tableThickness));
			backRest = glm::mat4(1.0f); backRest = glm::translate(backRest, glm::vec3(tableLength / 2 - tableThickness / 2, tableLegLength + restHeight / 2, 0));; backRest = glm::scale(backRest, glm::vec3(tableThickness, restHeight, tableWidth));

			glm::mat4 displace = glm::translate(glm::mat4(1.0f), glm::vec3(displaceX, 0, 0));
			displace = glm::rotate(displace, glm::radians(0.0f), glm::vec3(0, 1, 0));
			//DRAWING CHAIR 1
				shaderObject->setUniformMat4f("model", displace * tableTop);
				GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
				shaderObject->setUniformMat4f("model", displace * tableLeg[0]);
				GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
				shaderObject->setUniformMat4f("model", displace * tableLeg[1]);
				GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
				shaderObject->setUniformMat4f("model", displace * tableLeg[2]);
				GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
				shaderObject->setUniformMat4f("model", displace * tableLeg[3]);
				GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
				shaderObject->setUniformMat4f("model", displace * backRest);
				GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));

			displace = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -displaceZ));
			displace = glm::rotate(displace, glm::radians(90.0f), glm::vec3(0, 1, 0));
			//DRAWING CHAIR 2
			
			shaderObject->setUniformMat4f("model", displace * tableTop);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
			shaderObject->setUniformMat4f("model", displace * tableLeg[0]);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
			shaderObject->setUniformMat4f("model", displace * tableLeg[1]);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
			shaderObject->setUniformMat4f("model", displace * tableLeg[2]);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
			shaderObject->setUniformMat4f("model", displace * tableLeg[3]);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
			shaderObject->setUniformMat4f("model", displace * backRest);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));

			displace = glm::translate(glm::mat4(1.0f), glm::vec3(-displaceX, 0, 0));
			displace = glm::rotate(displace, glm::radians(180.0f), glm::vec3(0, 1, 0));
			//DRAWING CHAIR 3
			
			shaderObject->setUniformMat4f("model", displace * tableTop);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
			shaderObject->setUniformMat4f("model", displace * tableLeg[0]);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
			shaderObject->setUniformMat4f("model", displace * tableLeg[1]);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
			shaderObject->setUniformMat4f("model", displace * tableLeg[2]);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
			shaderObject->setUniformMat4f("model", displace * tableLeg[3]);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
			shaderObject->setUniformMat4f("model", displace * backRest);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));;

			displace = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, displaceZ));
			displace = glm::rotate(displace, glm::radians(270.0f), glm::vec3(0, 1, 0));
			//DRAWING CHAIR 4
			
			shaderObject->setUniformMat4f("model", displace* tableTop);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
			shaderObject->setUniformMat4f("model", displace* tableLeg[0]);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
			shaderObject->setUniformMat4f("model", displace* tableLeg[1]);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
			shaderObject->setUniformMat4f("model", displace* tableLeg[2]);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
			shaderObject->setUniformMat4f("model", displace* tableLeg[3]);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
			shaderObject->setUniformMat4f("model", displace* backRest);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
		}

			break;
		case Scenes::GODZILLA_VS_KINGKONG:
		{
			// do nothing for now
		}
			break;
		case Scenes::LEAP_OF_FAITH:
		{
			//do nothing for now
		}
			break;
		default:
		{

		}
			break;
		}
		shaderModel->bind();
		for (Prop e : props)
		{
			shaderModel->setUniformMat4f("model", e.model);
			e.m->Draw(shaderModel,"material.");
			GLCall(glBindTexture(GL_TEXTURE_2D, 0));
		}
	}
}


