﻿//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

#pragma once

#include "pch.h"
#include <collection.h>

namespace DatagramSocketSample
{
    namespace Common
    {
        // Suppress class "not consumable from JavaScript because it's not marked 'sealed'" warning
        // currently emitted despite the WebHostHidden attribute
        #pragma warning(push)
        #pragma warning(disable: 4449)
        /// <summary>
        /// Typical implementation of Page that provides several important conveniences: application
        /// view state to visual state mapping, GoBack and GoHome event handlers, and a default view
        /// model.
        /// </summary>
        [Windows::Foundation::Metadata::WebHostHidden]
        public ref class LayoutAwarePage : Windows::UI::Xaml::Controls::Page
        {
        internal:
            LayoutAwarePage();
        public:
            void StartLayoutUpdates(Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
            void StopLayoutUpdates(Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
            void InvalidateVisualState();
            static property Windows::UI::Xaml::DependencyProperty^ DefaultViewModelProperty
            {
                Windows::UI::Xaml::DependencyProperty^ get();
            };
            property Windows::Foundation::Collections::IObservableMap<Platform::String^, Object^>^ DefaultViewModel
            {
                Windows::Foundation::Collections::IObservableMap<Platform::String^, Object^>^ get();
                void set(Windows::Foundation::Collections::IObservableMap<Platform::String^, Object^>^ value);
            }

        protected:
            virtual void GoHome(Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
            virtual void GoBack(Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
            virtual Platform::String^ DetermineVisualState(double width);

        private:
            Platform::Collections::Map<Platform::String^, Object^>^ _defaultViewModel;
            Windows::Foundation::EventRegistrationToken _windowSizeEventToken;
            Platform::Collections::Vector<Windows::UI::Xaml::Controls::Control^>^ _layoutAwareControls;
            void WindowSizeChanged(Object^ sender, Windows::UI::Core::WindowSizeChangedEventArgs^ e);
        };
        #pragma warning(pop)
    }
}