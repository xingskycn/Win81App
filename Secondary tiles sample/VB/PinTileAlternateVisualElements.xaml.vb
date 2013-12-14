﻿'*********************************************************
'
' Copyright (c) Microsoft. All rights reserved.
' THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
' ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
' IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
' PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
'
'*********************************************************

Imports Windows.UI.StartScreen

''' <summary>
''' An empty page that can be used on its own or navigated to within a Frame.
''' </summary>
Partial Public NotInheritable Class PinTileAlternateVisualElements
    Inherits Global.SDKTemplate.Common.LayoutAwarePage

    ' A pointer back to the main page.  This is needed if you want to call methods in MainPage such
    ' as NotifyUser()
    Private rootPage As MainPage = MainPage.Current
    Private appBar As AppBar

    Public Sub New()
        Me.InitializeComponent()
    End Sub

    ''' <summary>
    ''' Invoked when this page is about to be displayed in a Frame.
    ''' </summary>
    ''' <param name="e">Event data that describes how this page was reached.  The Parameter
    ''' property is typically used to configure the page.</param>
    Protected Overrides Sub OnNavigatedTo(ByVal e As NavigationEventArgs)
        ' Preserve the app bar
        appBar = rootPage.BottomAppBar
        ' this ensures the app bar is not shown in this scenario
        rootPage.BottomAppBar = Nothing
    End Sub

    ''' <summary>
    ''' Invoked when this page is about to be navigated out in a Frame
    ''' </summary>
    ''' <param name="e">Event data that describes how this page was reached.  The Parameter
    ''' property is typically used to configure the page.</param>
    Protected Overrides Sub OnNavigatingFrom(ByVal e As NavigatingCancelEventArgs)
        ' Restore the app bar
        rootPage.BottomAppBar = appBar
    End Sub
    ''' <summary>
    ''' This is the click handler for the 'PinButton' button.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    Private Async Sub PinButton_Click(ByVal sender As Object, ByVal e As RoutedEventArgs)
        Dim button As Button = TryCast(sender, Button)
        If button IsNot Nothing Then
            ' Prepare package images for our tile to be pinned
            Dim square70x70Logo As New Uri("ms-appx:///Assets/square70x70Tile-sdk.png")
            Dim square150x150Logo As New Uri("ms-appx:///Assets/square150x150Tile-sdk.png")
            Dim wide310x150Logo As New Uri("ms-appx:///Assets/wide310x150Tile-sdk.png")
            Dim square310x310Logo As New Uri("ms-appx:///Assets/square310x310Tile-sdk.png")
            Dim square30x30Logo As New Uri("ms-appx:///Assets/square30x30Tile-sdk.png")

            ' During creation of the secondary tile, an application may set additional arguments on the tile that will be passed in during activation.
            ' These arguments should be meaningful to the application. In this sample, we'll pass in the date and time the secondary tile was pinned.
            Dim tileActivationArguments As String = MainPage.logoSecondaryTileId & " WasPinnedAt=" & Date.Now.ToLocalTime().ToString()

            ' Create a Secondary tile with all the required arguments and set the preferred size to be the medium tile size.
            Dim secondaryTile As New SecondaryTile(MainPage.logoSecondaryTileId, "Title text shown on the tile", tileActivationArguments, square150x150Logo, TileSize.Square150x150)

            ' Only support of the small and medium tile sizes is mandatory.
            ' To have the larger tile sizes available the assets must be provided.
            secondaryTile.VisualElements.Wide310x150Logo = wide310x150Logo
            secondaryTile.VisualElements.Square310x310Logo = square310x310Logo

            ' If the asset for the small tile size is not provided, it will be created by scaling down the medium tile size asset.
            ' Thus, providing the asset for the small tile size is not mandatory, though is recommended to avoid scaling artifacts and can be overridden as shown below. 
            ' Note that the asset for the small tile size must be explicitly provided if alternates for the small tile size are also explicitly provided.
            secondaryTile.VisualElements.Square70x70Logo = square70x70Logo

            ' Like the background color, the square30x30 logo is inherited from the parent application tile by default. 
            ' Let's override it, just to see how that's done.
            secondaryTile.VisualElements.Square30x30Logo = square30x30Logo

            ' The display of the secondary tile name can be controlled for each tile size.
            secondaryTile.VisualElements.ShowNameOnSquare150x150Logo = False
            secondaryTile.VisualElements.ShowNameOnWide310x150Logo = True
            secondaryTile.VisualElements.ShowNameOnSquare310x310Logo = True

            ' Add the handler for the VisualElemets request.
            ' This is needed to add alternate tile options for a user to choose from for the supported tile sizes.
            AddHandler secondaryTile.VisualElementsRequested, AddressOf VisualElementsRequestedHandler

            ' Specify a foreground text value.
            ' The tile background color is inherited from the parent unless a separate value is specified.
            secondaryTile.VisualElements.ForegroundText = ForegroundText.Dark

            ' OK, the tile is created and we can now attempt to pin the tile.
            ' Note that the status message is updated when the async operation to pin the tile completes.
            Dim isPinned As Boolean = Await secondaryTile.RequestCreateForSelectionAsync(MainPage.GetElementRect(CType(sender, FrameworkElement)), Windows.UI.Popups.Placement.Below)

            If isPinned Then
                rootPage.NotifyUser("Secondary tile successfully pinned.", NotifyType.StatusMessage)
            Else
                rootPage.NotifyUser("Secondary tile not pinned.", NotifyType.ErrorMessage)
            End If
        End If
    End Sub

    ' Alternate tile options for the supported tile sizes are set in the handler.
    Private Sub VisualElementsRequestedHandler(ByVal sender As Object, ByVal args As VisualElementsRequestedEventArgs)
        ' Prepare the images for the alternate tile options 
        Dim alternate1Square70x70Logo As New Uri("ms-appx:///Assets/alternate1Square70x70Tile-sdk.png")
        Dim alternate1Square150x150Logo As New Uri("ms-appx:///Assets/alternate1Square150x150Tile-sdk.png")
        Dim alternate1Wide310x150Logo As New Uri("ms-appx:///Assets/alternate1Wide310x150Tile-sdk.png")
        Dim alternate1Square310x310Logo As New Uri("ms-appx:///Assets/alternate1Square310x310Tile-sdk.png")

        Dim alternate2Square70x70Logo As New Uri("ms-appx:///Assets/alternate2Square70x70Tile-sdk.png")
        Dim alternate2Square150x150Logo As New Uri("ms-appx:///Assets/alternate2Square150x150Tile-sdk.png")
        Dim alternate2Wide310x150Logo As New Uri("ms-appx:///Assets/alternate2Wide310x150Tile-sdk.png")
        Dim alternate2Square310x310Logo As New Uri("ms-appx:///Assets/alternate2Square310x310Tile-sdk.png")

        Dim alternate3Square70x70Logo As New Uri("ms-appx:///Assets/alternate3Square70x70Tile-sdk.png")
        Dim alternate3Square150x150Logo As New Uri("ms-appx:///Assets/alternate3Square150x150Tile-sdk.png")
        Dim alternate3Wide310x150Logo As New Uri("ms-appx:///Assets/alternate3Wide310x150Tile-sdk.png")
        Dim alternate3Square310x310Logo As New Uri("ms-appx:///Assets/alternate3Square310x310Tile-sdk.png")

        ' Set the assets for the alternate tile options.
        ' Note that up to 3 sets of alternate options can be provided.
        ' Each tile size in a given set will map to each other (for example, the second alternate medium tile option will map to the second alternate wide tile option).
        ' Note that if alternates are provided for the small tile size (square70x70 logo), the default option for the small tile size must be overridden as shown earlier. 
        ' If neither the default option nor the alternates for the small tile size are provided, then all the medium tile size options will be scaled down to their corresponding small tile size options. 
        args.Request.AlternateVisualElements(0).Square70x70Logo = alternate1Square70x70Logo
        args.Request.AlternateVisualElements(0).Square150x150Logo = alternate1Square150x150Logo
        args.Request.AlternateVisualElements(0).Wide310x150Logo = alternate1Wide310x150Logo
        args.Request.AlternateVisualElements(0).Square310x310Logo = alternate1Square310x310Logo

        ' Set the BackgoundColor, ForegroundText, and ShowName propreties for the alternate set.
        args.Request.AlternateVisualElements(0).BackgroundColor = Colors.Green
        args.Request.AlternateVisualElements(0).ForegroundText = ForegroundText.Dark
        args.Request.AlternateVisualElements(0).ShowNameOnSquare310x310Logo = True

        args.Request.AlternateVisualElements(1).Square70x70Logo = alternate2Square70x70Logo
        args.Request.AlternateVisualElements(1).Square150x150Logo = alternate2Square150x150Logo
        args.Request.AlternateVisualElements(1).Wide310x150Logo = alternate2Wide310x150Logo
        args.Request.AlternateVisualElements(1).Square310x310Logo = alternate2Square310x310Logo

        args.Request.AlternateVisualElements(1).BackgroundColor = Color.FromArgb(&HFF, &H51, &H33, &HAB)

        args.Request.AlternateVisualElements(1).ForegroundText = ForegroundText.Dark
        args.Request.AlternateVisualElements(1).ShowNameOnWide310x150Logo = True

        args.Request.AlternateVisualElements(2).Square70x70Logo = alternate3Square70x70Logo
        args.Request.AlternateVisualElements(2).Square150x150Logo = alternate3Square150x150Logo
        args.Request.AlternateVisualElements(2).Wide310x150Logo = alternate3Wide310x150Logo
        args.Request.AlternateVisualElements(2).Square310x310Logo = alternate3Square310x310Logo

        args.Request.AlternateVisualElements(2).BackgroundColor = Colors.Red
        args.Request.AlternateVisualElements(2).ForegroundText = ForegroundText.Light
        args.Request.AlternateVisualElements(2).ShowNameOnSquare150x150Logo = True
    End Sub
End Class