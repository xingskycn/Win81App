﻿//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

//
// MainPage.xaml.h
// Declaration of the MainPage.xaml class.
//

#pragma once

#include "pch.h"
#include "MainPage.g.h"
#include "Common\LayoutAwarePage.h" // Required by generated header
#include "Constants.h"

namespace AccountPictureName
{
    public enum class NotifyType
    {
        StatusMessage,
        ErrorMessage
    };

    public ref class MainPageSizeChangedEventArgs sealed
    {
    public:
        property double Width
        {
            double get()
            {
                return width;
            }

            void set(double value)
            {
                width = value;
            }
        }

    private:
        double width;
    };

    [Windows::Foundation::Metadata::WebHostHidden]
    public ref class MainPage sealed
    {
    public:
        MainPage();

        property Windows::ApplicationModel::Activation::ProtocolActivatedEventArgs^ ProtocolEvent
        {
            Windows::ApplicationModel::Activation::ProtocolActivatedEventArgs^ get() { return _protocolEventArgs; }
            void set(Windows::ApplicationModel::Activation::ProtocolActivatedEventArgs^ value) { _protocolEventArgs = value; }
        }

        property Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ LaunchArgs;

        void NotifyUser(Platform::String^ strMessage, NotifyType type);
        void LoadScenario(Platform::String^ scenarioName);
        event Windows::Foundation::EventHandler<Platform::Object^>^ ScenarioLoaded;
        event Windows::Foundation::EventHandler<MainPageSizeChangedEventArgs^>^ MainPageResized;


    private:
        void SetAccountPictureName(Platform::String^ strFeature);
        void PopulateScenarios();
        void InvalidateSize();
        void InvalidateLayout();
        ~MainPage();

        Platform::Collections::Vector<Object^>^ ScenarioList;
        Windows::UI::Xaml::Controls::Frame^ HiddenFrame;
        void Footer_Click(Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

        Windows::ApplicationModel::Activation::ProtocolActivatedEventArgs^ _protocolEventArgs;

    protected:
        virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
        void MainPage_SizeChanged(Object^ sender, Windows::UI::Xaml::SizeChangedEventArgs^ e);
        void Scenarios_SelectionChanged(Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);

    internal:
        static MainPage^ Current;
    };
}
