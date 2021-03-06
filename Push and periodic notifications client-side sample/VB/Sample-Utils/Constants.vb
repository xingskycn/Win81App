﻿' THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
' ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
' THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
' PARTICULAR PURPOSE.
'
' Copyright (c) Microsoft Corporation. All rights reserved

Imports System
Imports System.Collections.Generic
Imports System.Linq
Imports System.Text
Imports System.Threading.Tasks

Namespace Global.SDKTemplate
    Partial Public Class MainPage
        Public Const FEATURE_NAME As String = "Push and Periodic Notifications"
        Public Property Channel() As Windows.Networking.PushNotifications.PushNotificationChannel
        Public Property Notifier() As PushNotificationsHelper.Notifier
    End Class
End Namespace
