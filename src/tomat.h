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

#ifndef TOMAT_H
#define TOMAT_H

#include <Plasma/Applet>
#include <Plasma/Svg>

#include <QTimer>
#include <QString>


enum State {IDLE, WORKING, OK};

class Tomat : public Plasma::Applet
{
    Q_OBJECT

    public:
        Tomat(QObject *parent, const QVariantList &args);
        ~Tomat();

        void init();
        void paintInterface(QPainter *p,
                            const QStyleOptionGraphicsItem *option,
                            const QRect &contentsRect);
        void constraintsEvent(Plasma::Constraints constrants);
        void mousePressEvent(QGraphicsSceneMouseEvent *event);

        enum { MIN_WORK_TIME = 10*60 }; // minimum working time in seconds

    public slots:
        void toolTipAboutToShow();
        void toolTipHidden();
        void setState(State newState);

    protected:
        QString getTime();
        QString getToolTip();

    private slots:
        void resetToolTip();
        void updateTime();
        void reloadTheme();

    private:
        QTimer workingTimer;
        Plasma::Svg svg;
        State currentState; 
        State oldState; 
        int secondsWorking;
        
};

#endif

