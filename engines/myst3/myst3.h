/* Residual - A 3D game interpreter
 *
 * Residual is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the AUTHORS
 * file distributed with this source distribution.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 *
 */

#ifndef MYST3_ENGINE_H
#define MYST3_ENGINE_H

#include "engines/engine.h"

#include "common/system.h"
#include "common/random.h"

#include "engines/myst3/archive.h"
#include "engines/myst3/console.h"
#include "engines/myst3/database.h"
#include "engines/myst3/movie.h"
#include "engines/myst3/node.h"
#include "engines/myst3/scene.h"
#include "engines/myst3/script.h"

namespace Myst3 {

// Engine Debug Flags
enum {
	kDebugVariable = (1 << 0),
	kDebugSaveLoad = (1 << 1),
	kDebugNode     = (1 << 2),
	kDebugScript   = (1 << 3)
};

// View type
enum ViewType {
	kCube = 1,
	kFrame = 2
};

class Console;
class Variables;

class Myst3Engine : public Engine {

protected:
	// Engine APIs
	virtual Common::Error run();
	virtual GUI::Debugger *getDebugger() { return (GUI::Debugger *)_console; }
public:
	Variables *_vars;
	Common::RandomSource *_rnd;

	Myst3Engine(OSystem *syst, int gameFlags);
	virtual ~Myst3Engine();

	void goToNode(uint16 nodeID, uint8 roomID = 0);
	void loadNode(uint16 nodeID, uint8 roomID = 0, uint32 ageID = 0);
	void loadNodeCubeFaces(uint16 nodeID);
	void loadNodeFrame(uint16 nodeID);
	void runScriptsFromNode(uint16 nodeID, uint8 roomID = 0, uint32 ageID = 0);
	void runNodeInitScripts();

	void loadMovie(uint16 id, uint16 condition, bool resetCond, bool loop);

	void drawFrame();
	uint getFrameCount() { return _frameCount; }
private:
	OSystem *_system;
	Console *_console;
	
	Node *_node;
	Scene *_scene;
	Archive *_archive;
	Script *_scriptEngine;
	Database *_db;

	Common::Array<Movie *> _movies;

	ViewType _viewType;

	uint _frameCount;

	friend class Console;
};

} // end of namespace Myst3

#endif
