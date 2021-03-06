//
// Copyright (C) 2020 OpenSim Ltd.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#include "inet/visualizer/base/PathOsgVisualizerBase.h"

#include "inet/common/LayeredProtocolBase.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/OsgScene.h"
#include "inet/common/OsgUtils.h"
#include "inet/mobility/contract/IMobility.h"

#ifdef WITH_OSG
#include <osg/LineWidth>
#endif // ifdef WITH_OSG

namespace inet {

namespace visualizer {

#ifdef WITH_OSG

PathOsgVisualizerBase::PathOsgVisualization::PathOsgVisualization(const char *label, const std::vector<int>& path, osg::Node *node) :
    PathVisualization(label, path),
    node(node)
{
}

void PathOsgVisualizerBase::initialize(int stage)
{
    PathVisualizerBase::initialize(stage);
    if (!hasGUI()) return;
    if (stage == INITSTAGE_LOCAL) {
        auto canvas = visualizationTargetModule->getCanvas();
        lineManager = LineManager::getOsgLineManager(canvas);
    }
}

void PathOsgVisualizerBase::refreshDisplay() const
{
    PathVisualizerBase::refreshDisplay();
    // TODO switch to osg canvas when API is extended
    visualizationTargetModule->getCanvas()->setAnimationSpeed(pathVisualizations.empty() ? 0 : fadeOutAnimationSpeed, this);
}

const PathVisualizerBase::PathVisualization *PathOsgVisualizerBase::createPathVisualization(const char *label, const std::vector<int>& path, cPacket *packet) const
{
    std::vector<Coord> points;
    for (auto id : path) {
        auto node = getSimulation()->getModule(id);
        points.push_back(getPosition(node));
    }
    auto node = inet::osg::createPolyline(points, cFigure::ARROW_NONE, cFigure::ARROW_BARBED);
    node->setStateSet(inet::osg::createLineStateSet(lineColorSet.getColor(pathVisualizations.size()), lineStyle, lineWidth));
    return new PathOsgVisualization(label, path, node);
}

void PathOsgVisualizerBase::addPathVisualization(const PathVisualization *pathVisualization)
{
    PathVisualizerBase::addPathVisualization(pathVisualization);
    auto pathOsgVisualization = static_cast<const PathOsgVisualization *>(pathVisualization);
    auto scene = inet::osg::TopLevelScene::getSimulationScene(visualizationTargetModule);
    lineManager->addModulePath(pathVisualization);
    scene->addChild(pathOsgVisualization->node);
}

void PathOsgVisualizerBase::removePathVisualization(const PathVisualization *pathVisualization)
{
    PathVisualizerBase::removePathVisualization(pathVisualization);
    auto pathOsgVisualization = static_cast<const PathOsgVisualization *>(pathVisualization);
    auto node = pathOsgVisualization->node;
    lineManager->removeModulePath(pathVisualization);
    node->getParent(0)->removeChild(node);
}

void PathOsgVisualizerBase::setAlpha(const PathVisualization *pathVisualization, double alpha) const
{
    auto pathOsgVisualization = static_cast<const PathOsgVisualization *>(pathVisualization);
    auto node = pathOsgVisualization->node;
    auto stateSet = node->getOrCreateStateSet();
    auto material = static_cast<osg::Material *>(stateSet->getAttribute(osg::StateAttribute::MATERIAL));
    material->setAlpha(osg::Material::FRONT_AND_BACK, alpha);
}

#endif // ifdef WITH_OSG

} // namespace visualizer

} // namespace inet

