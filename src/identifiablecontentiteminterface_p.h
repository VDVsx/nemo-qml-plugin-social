/*
 * Copyright (C) 2013 Jolla Ltd. <chris.adams@jollamobile.com>
 *
 * You may use this file under the terms of the BSD license as follows:
 *
 * "Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Nemo Mobile nor the names of its contributors
 *     may be used to endorse or promote products derived from this
 *     software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 */

#ifndef IDENTIFIABLECONTENTITEMINTERFACE_P_H
#define IDENTIFIABLECONTENTITEMINTERFACE_P_H

#include "identifiablecontentiteminterface.h"
#include "socialnetworkinterface.h"

#include <QtCore/QObject>
#include <QtCore/QVariantMap>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QSslError>

class ContentItemInterfacePrivate;
class IdentifiableContentItemInterfacePrivate : public QObject
{
    Q_OBJECT

public:
    IdentifiableContentItemInterfacePrivate(IdentifiableContentItemInterface *parent = 0);
    ~IdentifiableContentItemInterfacePrivate();

    QNetworkReply *reply(); // returns currentReply
    void deleteReply();     // disconnect()s and then deleteLater()s currentReply, sets to null.  DOES NOT SET STATE.

    IdentifiableContentItemInterface *q;
    SocialNetworkInterface::Status status;
    SocialNetworkInterface::ErrorType error;
    QString identifier;
    QString errorMessage;

    bool needsReload;

public Q_SLOTS:
    void defaultRemoveHandler();
    void defaultReloadHandler();
    void defaultErrorHandler(QNetworkReply::NetworkError err);
    void defaultSslErrorsHandler(const QList<QSslError> &sslErrors);

private:
    ContentItemInterfacePrivate *d;
    QNetworkReply *currentReply; // may only be written to if status != Busy.  MUST be valid at all times, or zero.
    friend class IdentifiableContentItemInterface;
};

#endif // IDENTIFIABLECONTENTITEMINTERFACE_P_H
