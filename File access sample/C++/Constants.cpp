//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

#include "pch.h"
#include "MainPage.xaml.h"
#include "Constants.h"

using namespace SDKSample;

using namespace concurrency;
using namespace Platform;
using namespace Windows::Storage;
using namespace Windows::UI::Xaml::Controls;

Platform::Array<Scenario>^ MainPage::scenariosInner = ref new Platform::Array<Scenario>
{
    { "Creating a file",                                      "SDKSample.FileAccess.Scenario1" },
    { "Getting a file's parent folder",                       "SDKSample.FileAccess.Scenario2" },
    { "Writing and reading text in a file",                   "SDKSample.FileAccess.Scenario3" },
    { "Writing and reading bytes in a file",                  "SDKSample.FileAccess.Scenario4" },
    { "Writing and reading using a stream",                   "SDKSample.FileAccess.Scenario5" },
    { "Displaying file properties",                           "SDKSample.FileAccess.Scenario6" },
    { "Persisting access to a storage item for future use",   "SDKSample.FileAccess.Scenario7" },
    { "Copying a file",                                       "SDKSample.FileAccess.Scenario8" },
    { "Comparing two files to see if they are the same file", "SDKSample.FileAccess.Scenario9" },
    { "Deleting a file",                                      "SDKSample.FileAccess.Scenario10" },
    { "Attempting to get a file with no error on failure",    "SDKSample.FileAccess.Scenario11" },
};

void MainPage::Initialize()
{
    sampleFile = nullptr;
    mruToken = nullptr;
    falToken = nullptr;
}

void MainPage::ResetScenarioOutput(TextBlock^ output)
{
    // clear Error/Status
    NotifyUser("", NotifyType::ErrorMessage);
    NotifyUser("", NotifyType::StatusMessage);
    // clear scenario output
    output->Text = "";
}

void MainPage::ValidateFile()
{
    create_task(KnownFolders::PicturesLibrary->GetFileAsync(Filename)).then([this](task<StorageFile^> getFileTask)
    {
        try
        {
            sampleFile = getFileTask.get();
        }
        catch (Platform::Exception^)
        {
            // If file doesn't exist, indicate users to use scenario 1
            NotifyUserFileNotExist();
        }
    });
}

void MainPage::NotifyUserFileNotExist()
{
    NotifyUser("The file '" + Filename + "' does not exist. Use scenario one to create this file.", NotifyType::ErrorMessage);
}

void MainPage::HandleFileNotFoundException(Platform::COMException^ e)
{
    if (e->HResult == 0x80070002) // Catch FileNotExistException
    {
        NotifyUserFileNotExist();
    }
    else
    {
        throw e;
    }
}
