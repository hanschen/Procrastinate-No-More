/***************************************************************************
* Copyright © 2011 Hans Chen <contact@hanschen.org>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the
* Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
***************************************************************************/

#include "tomat.h"

#include <QtCore/QSizeF>
#include <QtCore/QTimer>
#include <QtGui/QGraphicsSceneMouseEvent>
#include <QtGui/QPainter>

#include <Plasma/Svg>
#include <Plasma/Theme>
#include <Plasma/ToolTipContent>
#include <Plasma/ToolTipManager>

Tomat::Tomat(QObject *parent, const QVariantList &args)
    : Plasma::Applet(parent, args),
      svg(this)
{
    currentState = IDLE;
    oldState = IDLE;

    svg.setImagePath(Plasma::Theme::defaultTheme()->imagePath("widgets/work_state"));
    svg.setContainsMultipleImages(true);

    setAspectRatioMode(Plasma::Square);
    setBackgroundHints(DefaultBackground);
}

Tomat::~Tomat()
{
}

void Tomat::init()
{
    Plasma::ToolTipManager::self()->registerWidget(this);

    connect(&workingTimer, SIGNAL(timeout()), this, SLOT(updateTime()));
    connect(Plasma::Theme::defaultTheme(), SIGNAL(themeChanged()), this, SLOT(reloadTheme()));
    connect(this, SIGNAL(activate()), this, SLOT(manuallySwitchState()));
}

void Tomat::paintInterface(QPainter *p,
                           const QStyleOptionGraphicsItem *option,
                           const QRect &contentsRect)
{
    const double margins = 4.0; // thickness of margins around icon in px

    Q_UNUSED(option)
    
    p->setRenderHint(QPainter::SmoothPixmapTransform);
    p->setRenderHint(QPainter::Antialiasing);

    double width = contentsRect.width(),
           height = contentsRect.height();

    QString elementid;
    switch (currentState) {
        case IDLE:
            elementid = "idle";
            break;
        case WORKING:
            elementid = "working";
            break;
        case OK:
            elementid = "ok";
            break;
    }

    if (width < height) {
        height = width;
    } else {
        width = height;
    }

    p->save();

    svg.resize(QSizeF(width - margins, height - margins));
    svg.paint(p,
             (int)contentsRect.left() + margins/2,
             (int)contentsRect.top() + margins/2,
             elementid);

    p->restore();
}

void Tomat::constraintsEvent(Plasma::Constraints constraints)
{
    if (constraints & Plasma::FormFactorConstraint) {
        if (formFactor() == Plasma::Horizontal || formFactor() == Plasma::Vertical) {
            setPreferredSize(-1,-1);
        } else {
            setPreferredSize(100, 100);
        }

    }

    if (formFactor() == Plasma::Planar || formFactor() == Plasma::MediaCenter) {
        setMinimumSize(32,32);
    } else {
        setMinimumSize(0,0);
    }

    update();
}

void Tomat::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    if (event->buttons() == Qt::LeftButton &&
        contentsRect().contains(event->pos())) {
        manuallySwitchState();
        return;
    }

    Applet::mousePressEvent(event);
}

void Tomat::toolTipAboutToShow()
{
    Plasma::ToolTipContent toolTip;
    toolTip.setMainText(getToolTip());
    Plasma::ToolTipManager::self()->setContent(this, toolTip);
}

void Tomat::toolTipHidden()
{
}

void Tomat::setState(State newState)
{
    if (newState == IDLE) {
        workingTimer.stop();
        QTimer::singleShot(60*1000, this, SLOT(resetToolTip()));
        Plasma::ToolTipManager::self()->show(this);
    }
    else if (newState == WORKING) {
        secondsWorking = 0;
        workingTimer.start(1000);
    }

    oldState = currentState;
    currentState = newState;
    update();
}

void Tomat::manuallySwitchState()
{
    if (currentState == IDLE) {
        setState(WORKING);
    } else {
        setState(IDLE);
    }
}

QString Tomat::getTime()
{
    const int secondsInMinute = 60;
    const int secondsInHour = 60*60;

    QString time;

    int hours = secondsWorking/secondsInHour;
    int minutes = (secondsWorking%secondsInHour)/secondsInMinute;

    QString hourText = (hours == 1) ? i18n("hour")
                                    : i18n("hours");
    QString minuteText = (minutes == 1) ? i18n("minute")
                                        : i18n("minutes");

    if (hours > 0) {
        time = i18n("%1 %2 and ").arg(QString::number(hours))
                                 .arg(hourText);
    }
    time = time + i18n("%1 %2").arg(QString::number(minutes))
                               .arg(minuteText);
        
    return time;
}

QString Tomat::getToolTip()
{
    QString toolTip;

    if (currentState == IDLE) {
        if (oldState == IDLE) {
            toolTip = "Idle";
        }
        else if (oldState == WORKING) {
            toolTip = i18n("Not good, only worked for %1").arg(getTime());
        }
        else if (oldState == OK) {
            toolTip = i18n("Good! Worked for %1").arg(getTime());
        }
    } else {
        toolTip = i18n("Working for %1").arg(getTime());
    }

    return toolTip;
}

void Tomat::resetToolTip()
{
    // resets the tool tip to "Idle"
    if (currentState == IDLE) {
        oldState = IDLE;
    }
}

void Tomat::updateTime()
{
    secondsWorking++;
    if (currentState == WORKING && secondsWorking >= MIN_WORK_TIME) {
        setState(OK);
    }
}

void Tomat::reloadTheme()
{
    svg.setImagePath(Plasma::Theme::defaultTheme()->imagePath("widgets/work_state"));
}

K_EXPORT_PLASMA_APPLET(tomat, Tomat)
