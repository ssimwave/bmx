/*
 * Copyright (C) 2013, British Broadcasting Corporation
 * All Rights Reserved.
 *
 * Author: Philip de Nier
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the British Broadcasting Corporation nor the names
 *       of its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <bmx/mxf_helper/DataMXFDescriptorHelper.h>
#include <bmx/mxf_helper/ANCDataMXFDescriptorHelper.h>
#include <bmx/mxf_helper/VBIDataMXFDescriptorHelper.h>
#include <bmx/mxf_helper/TimedTextMXFDescriptorHelper.h>
#include <bmx/BMXException.h>
#include <bmx/Logging.h>

using namespace std;
using namespace bmx;
using namespace mxfpp;



EssenceType DataMXFDescriptorHelper::IsSupported(mxfpp::FileDescriptor *file_descriptor, mxfUL alternative_ec_label)
{
    GenericDataEssenceDescriptor *data_descriptor = dynamic_cast<GenericDataEssenceDescriptor*>(file_descriptor);
    if (!data_descriptor)
        return UNKNOWN_ESSENCE_TYPE;

    EssenceType essence_type = ANCDataMXFDescriptorHelper::IsSupported(file_descriptor, alternative_ec_label);
    if (essence_type)
        return essence_type;
    essence_type = VBIDataMXFDescriptorHelper::IsSupported(file_descriptor, alternative_ec_label);
    if (essence_type)
        return essence_type;
    essence_type = TimedTextMXFDescriptorHelper::IsSupported(file_descriptor, alternative_ec_label);
    if (essence_type)
        return essence_type;

    return DATA_ESSENCE;
}

std::unique_ptr<DataMXFDescriptorHelper> DataMXFDescriptorHelper::Create(mxfpp::FileDescriptor *file_descriptor,
                                                                         uint16_t mxf_version,
                                                                         mxfUL alternative_ec_label)
{
    std::unique_ptr<DataMXFDescriptorHelper> helper;
    if (ANCDataMXFDescriptorHelper::IsSupported(file_descriptor, alternative_ec_label))
        helper = std::make_unique<ANCDataMXFDescriptorHelper>();
    else if (VBIDataMXFDescriptorHelper::IsSupported(file_descriptor, alternative_ec_label))
        helper = std::make_unique<VBIDataMXFDescriptorHelper>();
    else if (TimedTextMXFDescriptorHelper::IsSupported(file_descriptor, alternative_ec_label))
        helper = std::make_unique<TimedTextMXFDescriptorHelper>();
    else
        helper = std::make_unique<DataMXFDescriptorHelper>();

    helper->Initialize(file_descriptor, mxf_version, alternative_ec_label);

    return helper;
}

bool DataMXFDescriptorHelper::IsSupported(EssenceType essence_type)
{
    return ANCDataMXFDescriptorHelper::IsSupported(essence_type) ||
           VBIDataMXFDescriptorHelper::IsSupported(essence_type) ||
           TimedTextMXFDescriptorHelper::IsSupported(essence_type);
}

std::unique_ptr<MXFDescriptorHelper> DataMXFDescriptorHelper::Create(EssenceType essence_type)
{
    BMX_ASSERT(IsSupported(essence_type));

    std::unique_ptr<DataMXFDescriptorHelper> helper;
    if (ANCDataMXFDescriptorHelper::IsSupported(essence_type))
        helper = std::make_unique<ANCDataMXFDescriptorHelper>();
    else if (VBIDataMXFDescriptorHelper::IsSupported(essence_type))
        helper = std::make_unique<VBIDataMXFDescriptorHelper>();
    else
        helper = std::make_unique<TimedTextMXFDescriptorHelper>();

    helper->SetEssenceType(essence_type);

    return helper;
}

DataMXFDescriptorHelper::DataMXFDescriptorHelper()
: MXFDescriptorHelper()
{
    mEssenceType = DATA_ESSENCE;
}

DataMXFDescriptorHelper::~DataMXFDescriptorHelper()
{
}

void DataMXFDescriptorHelper::Initialize(FileDescriptor *file_descriptor, uint16_t mxf_version, mxfUL alternative_ec_label)
{
    MXFDescriptorHelper::Initialize(file_descriptor, mxf_version, alternative_ec_label);

    mEssenceType = DATA_ESSENCE;
}

FileDescriptor* DataMXFDescriptorHelper::CreateFileDescriptor(HeaderMetadata *header_metadata)
{
    (void)header_metadata;

    // implemented by child classes only
    BMX_ASSERT(false);
    return 0;
}

uint32_t DataMXFDescriptorHelper::GetSampleSize()
{
    // implemented by child classes only
    BMX_ASSERT(false);
    return 0;
}

mxfUL DataMXFDescriptorHelper::ChooseEssenceContainerUL() const
{
    // implemented by child classes only
    BMX_ASSERT(false);
    return g_Null_UL;
}

