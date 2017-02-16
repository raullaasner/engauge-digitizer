/******************************************************************************************************
 * (C) 2017 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DataKey.h"
#include "EnumsToQt.h"
#include "GraphicsItemType.h"
#include "Logger.h"
#include <QGraphicsScene>
#include <QPointF>
#include "ScaleBar.h"
#include "ScaleEndpoint.h"
#include "ZValues.h"

ScaleBar::ScaleBar(QGraphicsScene  &scene,
                   const QPointF &posScreen) :
  m_endpoint1 (0),
  m_endpoint2 (0)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "ScaleBar::ScaleBar";

  setData (DATA_KEY_GRAPHICS_ITEM_TYPE, QVariant (GRAPHICS_ITEM_TYPE_SCALE_BAR));

  // Make this transparent now, but always visible so hover events work
  scene.addItem (this);
  setPen (QPen (Qt::transparent));
  setZValue (Z_VALUE_CURVE);
  setVisible (true);
  setAcceptHoverEvents (true);
  setFlags (QGraphicsItem::ItemIsFocusable);

  // Initially the line starts and stops at the same spot. As cursor is moved, one of the end points will follow it
  setLine (QLineF (posScreen,
                   posScreen));

  m_endpoint1 = new ScaleEndpoint (scene,
                                   this,
                                   posScreen);
  m_endpoint2 = new ScaleEndpoint (scene,
                                   this,
                                   posScreen);

  // Make the second endpoint follow the cursor
  m_endpoint2->setSelected (true);
}

ScaleBar::~ScaleBar ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "ScaleBar::~ScaleBar";
}
