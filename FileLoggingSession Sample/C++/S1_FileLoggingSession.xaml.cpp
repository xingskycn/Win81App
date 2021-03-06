//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
//
//*********************************************************

//
// S1_FileLoggingSession.xaml.cpp
// Implementation of the S1_FileLoggingSession class
//

#include "pch.h"
#include "S1_FileLoggingSession.xaml.h"
#include "MainPage.xaml.h"
#include "LoggingScenario.h"

using namespace SDKSample;
using namespace SDKSample::FileLoggingSession;

using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;

S1_FileLoggingSession::S1_FileLoggingSession()
{
    // This sample UI is interested in events from
    // the LoggingScenario class so the UI can be updated. 
    LoggingScenario->StatusChanged += ref new StatusChangedHandler(this, &S1_FileLoggingSession::OnStatusChanged);
    InitializeComponent();
}

void S1_FileLoggingSession::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e)
{
    UpdateControls();
}

// This function finds a TextBlock's ScrollViewer.
Windows::UI::Xaml::Controls::ScrollViewer^ S1_FileLoggingSession::FindScrollViewer(DependencyObject^ depObject)
{
    if (depObject == nullptr)
    {
        return nullptr;
    }

    int countThisLevel = Windows::UI::Xaml::Media::VisualTreeHelper::GetChildrenCount(depObject);
    if (countThisLevel <= 0)
    {
        return nullptr;
    }

    for (int childIndex = 0; childIndex < countThisLevel; childIndex++)
    {
        DependencyObject^ childDepObject = Windows::UI::Xaml::Media::VisualTreeHelper::GetChild(depObject, childIndex);
        ScrollViewer^ sv = dynamic_cast<ScrollViewer^>(childDepObject);
        if (sv != nullptr)
        {
            return sv;
        }

        sv = FindScrollViewer(childDepObject);
        if (sv != nullptr)
        {
            return sv;
        }
    }

    return nullptr;
}

// Add a message to the UI control which displays status while the sample is running.
void S1_FileLoggingSession::AddMessage(Platform::String^ message)
{
    Platform::String^ messageToAdd = "";
    messageToAdd += message;
    messageToAdd += "\r\n";
    StatusMessageList->Text += messageToAdd;
    StatusMessageList->Select(StatusMessageList->Text->Length(), 0);

    ScrollViewer^ sv = FindScrollViewer(StatusMessageList);
    if (sv != nullptr)
    {
        sv->ChangeView(nullptr, StatusMessageList->ActualHeight, nullptr);
    }
    
}

// Call AddMessage on the UI thread.
task<void> S1_FileLoggingSession::AddMessageDispatch(Platform::String^ message)
{
    return create_task(Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::High, ref new Windows::UI::Core::DispatchedHandler([=](){
        AddMessage(message);
    })));
}

// AddLogFileMessageDispatch updates the UI with status information when
// a new log file is created. 
task<void> S1_FileLoggingSession::AddLogFileMessageDispatch(Platform::String^ message, const std::wstring& logFileFullPath)
{
    return create_task(Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::High, ref new Windows::UI::Core::DispatchedHandler([=](){

        // On the UI thread...

        Platform::String^ finalMessage;
        if (logFileFullPath.empty() == false)
        {
            // Add a message to the UI indicating a new log file was created.

            AppLogFolderLabel->Visibility = Windows::UI::Xaml::Visibility::Visible;
            AppLogFolder->Visibility = Windows::UI::Xaml::Visibility::Visible;
            std::wstring justDirectoryName;
            std::wstring justFileName;
            std::wstring::size_type posLastSlash = logFileFullPath.find_last_of(L'\\');
            if (posLastSlash > 0 && posLastSlash < logFileFullPath.size() - 1)
            {
                justDirectoryName = logFileFullPath.substr(0, posLastSlash);
                justFileName = logFileFullPath.substr(posLastSlash + 1, logFileFullPath.size() - (posLastSlash + 1));
            }
            finalMessage = message + ": " + ref new Platform::String(justFileName.c_str());
            AppLogFolder->Text = ref new Platform::String(justDirectoryName.c_str());
            ViewLogInfo->Visibility = Windows::UI::Xaml::Visibility::Visible;
            ViewLogInfo->Text = "To view the contents of the ETL files:\r\n" +
                                "Using tracerpt to create an XML file: tracerpt.exe \"" +
                                ref new Platform::String(logFileFullPath.c_str()) +
                                "\" -of XML -o LogFile.xml\r\n" +
                                "Using the Windows Performance Toolkit (WPT): wpa.exe \"" +
                                ref new Platform::String(logFileFullPath.c_str()) + "\"";
        }
        else
        {
            finalMessage = message + ": none, nothing logged since saving the last file.";
        }
        AddMessage(finalMessage);
    })));
}

// For this sample, the logging sample code is in LoggingScenario.
// The following method handles status events from LoggingScenario as 
// it runs the scenario. 
void S1_FileLoggingSession::OnStatusChanged(SDKSample::FileLoggingSession::LoggingScenario ^sender, SDKSample::FileLoggingSession::LoggingScenarioEventArgs ^e)
{
    if (e->Type == LoggingScenarioEventType::BusyStatusChanged)
    {
        create_task(Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::High, ref new Windows::UI::Core::DispatchedHandler([=](){
            UpdateControls();
        })));
    }
    else if (e->Type == LoggingScenarioEventType::LogFileGenerated)
    {
        AddLogFileMessageDispatch("LogFileGenerated", e->LogFileFullPath).then([](){
        });
    }
    else if (e->Type == LoggingScenarioEventType::LogFileGeneratedAtSuspend)
    {
        AddLogFileMessageDispatch("Log file at suspend", e->LogFileFullPath).then([](){
        });
    }
    else if (e->Type == LoggingScenarioEventType::LogFileGeneratedAtDisable)
    {
        AddLogFileMessageDispatch("Log file at disable", e->LogFileFullPath).then([](){
        });
    }
    else if (e->Type == LoggingScenarioEventType::LoggingEnabledDisabled)
    {
        Platform::String^ message = "Logging has been " + (e->Enabled ? "enabled" : "disabled") + ".";
        AddMessageDispatch(message);
    }
}

// Adjust UI controls based on what the sample is doing.
void S1_FileLoggingSession::UpdateControls()
{
    if (LoggingScenario->LoggingEnabled)
    {
        InputTextBlock1->Text = "Logging is enabled. Click 'Disable Logging' to disable logging. With logging enabled, you can click 'Log Messages' to use the logging API to generate log files.";
        EnableDisableLoggingButton->Content = "Disable Logging";
        if (LoggingScenario->IsBusy)
        {
            EnableDisableLoggingButton->IsEnabled = false;
            DoScenarioButton->IsEnabled = false;
        }
        else
        {
            EnableDisableLoggingButton->IsEnabled = true;
            DoScenarioButton->IsEnabled = true;
        }
    }
    else
    {
        InputTextBlock1->Text = "Logging is disabled. Click 'Enable Logging' to enable logging. After you enable logging you can click 'Log Messages' to use the logging API to generate log files.";
        EnableDisableLoggingButton->Content = "Enable Logging";
        DoScenarioButton->IsEnabled = false;
        if (LoggingScenario->IsBusy)
        {
            EnableDisableLoggingButton->IsEnabled = false;
        }
        else
        {
            EnableDisableLoggingButton->IsEnabled = true;
        }
    }
}

// Enabled/disabled logging.
void S1_FileLoggingSession::EnableDisableLogging(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
    if (LoggingScenario->LoggingEnabled)
    {
        MainPage::Current->NotifyUser("Disabling logging...", NotifyType::StatusMessage);
    }
    else
    {
        MainPage::Current->NotifyUser("Enabling logging...", NotifyType::StatusMessage);
    }

    LoggingScenario->ToggleLoggingEnabledDisabledAsync().then([this](bool isEnabled) {

        UNREFERENCED_PARAMETER(isEnabled);
        
        UpdateControls();

        if (this->LoggingScenario->LoggingEnabled)
        {
            MainPage::Current->NotifyUser("Logging enabled.", NotifyType::StatusMessage);
        }
        else
        {
            MainPage::Current->NotifyUser("Logging disabled.", NotifyType::StatusMessage);
        }

    }, task_continuation_context::use_current());
}

// Run a sample scenario which logs lots of messages to produce several log files. 
void S1_FileLoggingSession::DoScenario(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
    DoScenarioButton->IsEnabled = false;
    MainPage::Current->NotifyUser("Scenario running...", NotifyType::StatusMessage);
    // Allow the UI to update...
    create_task(DoScenarioButton->Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::High, ref new Windows::UI::Core::DispatchedHandler([=](){}))).then([this]()
    {
        // Run the scenario asynchronously.
        return LoggingScenario->DoScenarioAsync();
    }).then([this](task<void> previousTask){
        // After the scenario completes, re-enable UI controls and display a message.
        DoScenarioButton->IsEnabled = true;
        MainPage::Current->NotifyUser("Scenario finished.", NotifyType::StatusMessage);
    }, task_continuation_context::use_current());
}
