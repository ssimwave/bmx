/*
 * Copyright (C) 2010, British Broadcasting Corporation
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

#include <cstring>

#include <bmx/mxf_helper/PictureMXFDescriptorHelper.h>
#include <bmx/mxf_helper/D10MXFDescriptorHelper.h>
#include <bmx/mxf_helper/DVMXFDescriptorHelper.h>
#include <bmx/mxf_helper/AVCMXFDescriptorHelper.h>
#include <bmx/mxf_helper/AVCIMXFDescriptorHelper.h>
#include <bmx/mxf_helper/UncCDCIMXFDescriptorHelper.h>
#include <bmx/mxf_helper/UncRGBAMXFDescriptorHelper.h>
#include <bmx/mxf_helper/MPEG2LGMXFDescriptorHelper.h>
#include <bmx/mxf_helper/VC3MXFDescriptorHelper.h>
#include <bmx/mxf_helper/MJPEGMXFDescriptorHelper.h>
#include <bmx/mxf_helper/VC2MXFDescriptorHelper.h>
#include <bmx/mxf_helper/RDD36MXFDescriptorHelper.h>
#include <bmx/mxf_helper/JPEG2000MXFDescriptorHelper.h>
#include <bmx/MXFUtils.h>
#include <bmx/BMXTypes.h>
#include <bmx/BMXException.h>
#include <bmx/Logging.h>

#include <mxf/mxf_avid.h>

using namespace std;
using namespace bmx;
using namespace mxfpp;



EssenceType PictureMXFDescriptorHelper::IsSupported(FileDescriptor *file_descriptor, mxfUL alternative_ec_label)
{
    GenericPictureEssenceDescriptor *picture_descriptor =
        dynamic_cast<GenericPictureEssenceDescriptor*>(file_descriptor);
    if (!picture_descriptor)
        return UNKNOWN_ESSENCE_TYPE;

    EssenceType essence_type = D10MXFDescriptorHelper::IsSupported(file_descriptor, alternative_ec_label);
    if (essence_type)
        return essence_type;
    essence_type = DVMXFDescriptorHelper::IsSupported(file_descriptor, alternative_ec_label);
    if (essence_type)
        return essence_type;
    essence_type = AVCIMXFDescriptorHelper::IsSupported(file_descriptor, alternative_ec_label);
    if (essence_type)
        return essence_type;
    essence_type = AVCMXFDescriptorHelper::IsSupported(file_descriptor, alternative_ec_label);
    if (essence_type)
        return essence_type;
    essence_type = UncCDCIMXFDescriptorHelper::IsSupported(file_descriptor, alternative_ec_label);
    if (essence_type)
        return essence_type;
    essence_type = UncRGBAMXFDescriptorHelper::IsSupported(file_descriptor, alternative_ec_label);
    if (essence_type)
        return essence_type;
    essence_type = MPEG2LGMXFDescriptorHelper::IsSupported(file_descriptor, alternative_ec_label);
    if (essence_type)
        return essence_type;
    essence_type = RDD36MXFDescriptorHelper::IsSupported(file_descriptor, alternative_ec_label);
    if (essence_type)
        return essence_type;
    essence_type = JPEG2000MXFDescriptorHelper::IsSupported(file_descriptor, alternative_ec_label);
    if (essence_type)
        return essence_type;
    essence_type = VC2MXFDescriptorHelper::IsSupported(file_descriptor, alternative_ec_label);
    if (essence_type)
        return essence_type;
    essence_type = VC3MXFDescriptorHelper::IsSupported(file_descriptor, alternative_ec_label);
    if (essence_type)
        return essence_type;
    essence_type = MJPEGMXFDescriptorHelper::IsSupported(file_descriptor, alternative_ec_label);
    if (essence_type)
        return essence_type;

    return PICTURE_ESSENCE;
}

std::unique_ptr<PictureMXFDescriptorHelper> PictureMXFDescriptorHelper::Create(FileDescriptor *file_descriptor,
                                                                               uint16_t mxf_version,
                                                                               mxfUL alternative_ec_label)
{
    std::unique_ptr<PictureMXFDescriptorHelper> helper;
    if (D10MXFDescriptorHelper::IsSupported(file_descriptor, alternative_ec_label))
        helper = std::make_unique<D10MXFDescriptorHelper>();
    else if (DVMXFDescriptorHelper::IsSupported(file_descriptor, alternative_ec_label))
        helper = std::make_unique<DVMXFDescriptorHelper>();
    else if (AVCIMXFDescriptorHelper::IsSupported(file_descriptor, alternative_ec_label))
        helper = std::make_unique<AVCIMXFDescriptorHelper>();
    else if (AVCMXFDescriptorHelper::IsSupported(file_descriptor, alternative_ec_label))
        helper = std::make_unique<AVCMXFDescriptorHelper>();
    else if (UncCDCIMXFDescriptorHelper::IsSupported(file_descriptor, alternative_ec_label))
        helper = std::make_unique<UncCDCIMXFDescriptorHelper>();
    else if (UncRGBAMXFDescriptorHelper::IsSupported(file_descriptor, alternative_ec_label))
        helper = std::make_unique<UncRGBAMXFDescriptorHelper>();
    else if (MPEG2LGMXFDescriptorHelper::IsSupported(file_descriptor, alternative_ec_label))
        helper = std::make_unique<MPEG2LGMXFDescriptorHelper>();
    else if (RDD36MXFDescriptorHelper::IsSupported(file_descriptor, alternative_ec_label))
        helper = std::make_unique<RDD36MXFDescriptorHelper>();
    else if (JPEG2000MXFDescriptorHelper::IsSupported(file_descriptor, alternative_ec_label))
        helper = std::make_unique<JPEG2000MXFDescriptorHelper>();
    else if (VC2MXFDescriptorHelper::IsSupported(file_descriptor, alternative_ec_label))
        helper = std::make_unique<VC2MXFDescriptorHelper>();
    else if (VC3MXFDescriptorHelper::IsSupported(file_descriptor, alternative_ec_label))
        helper = std::make_unique<VC3MXFDescriptorHelper>();
    else if (MJPEGMXFDescriptorHelper::IsSupported(file_descriptor, alternative_ec_label))
        helper = std::make_unique<MJPEGMXFDescriptorHelper>();
    else
        helper = std::make_unique<PictureMXFDescriptorHelper>();

    helper->Initialize(file_descriptor, mxf_version, alternative_ec_label);

    return helper;
}

bool PictureMXFDescriptorHelper::IsSupported(EssenceType essence_type)
{
    return D10MXFDescriptorHelper::IsSupported(essence_type) ||
           DVMXFDescriptorHelper::IsSupported(essence_type) ||
           AVCIMXFDescriptorHelper::IsSupported(essence_type) ||
           AVCMXFDescriptorHelper::IsSupported(essence_type) ||
           UncCDCIMXFDescriptorHelper::IsSupported(essence_type) ||
           UncRGBAMXFDescriptorHelper::IsSupported(essence_type) ||
           MPEG2LGMXFDescriptorHelper::IsSupported(essence_type) ||
           RDD36MXFDescriptorHelper::IsSupported(essence_type) ||
           JPEG2000MXFDescriptorHelper::IsSupported(essence_type) ||
           VC2MXFDescriptorHelper::IsSupported(essence_type) ||
           VC3MXFDescriptorHelper::IsSupported(essence_type) ||
           MJPEGMXFDescriptorHelper::IsSupported(essence_type);
}

std::unique_ptr<MXFDescriptorHelper> PictureMXFDescriptorHelper::Create(EssenceType essence_type)
{
    BMX_ASSERT(IsSupported(essence_type));

    std::unique_ptr<PictureMXFDescriptorHelper> helper;
    if (D10MXFDescriptorHelper::IsSupported(essence_type))
        helper = std::make_unique<D10MXFDescriptorHelper>();
    else if (DVMXFDescriptorHelper::IsSupported(essence_type))
        helper = std::make_unique<DVMXFDescriptorHelper>();
    else if (AVCIMXFDescriptorHelper::IsSupported(essence_type))
        helper = std::make_unique<AVCIMXFDescriptorHelper>();
    else if (AVCMXFDescriptorHelper::IsSupported(essence_type))
        helper = std::make_unique<AVCMXFDescriptorHelper>();
    else if (UncCDCIMXFDescriptorHelper::IsSupported(essence_type))
        helper = std::make_unique<UncCDCIMXFDescriptorHelper>();
    else if (UncRGBAMXFDescriptorHelper::IsSupported(essence_type))
        helper = std::make_unique<UncRGBAMXFDescriptorHelper>();
    else if (MPEG2LGMXFDescriptorHelper::IsSupported(essence_type))
        helper = std::make_unique<MPEG2LGMXFDescriptorHelper>();
    else if (RDD36MXFDescriptorHelper::IsSupported(essence_type))
        helper = std::make_unique<RDD36MXFDescriptorHelper>();
    else if (JPEG2000MXFDescriptorHelper::IsSupported(essence_type))
        helper = std::make_unique<JPEG2000MXFDescriptorHelper>();
    else if (VC2MXFDescriptorHelper::IsSupported(essence_type))
        helper = std::make_unique<VC2MXFDescriptorHelper>();
    else if (VC3MXFDescriptorHelper::IsSupported(essence_type))
        helper = std::make_unique<VC3MXFDescriptorHelper>();
    else if (MJPEGMXFDescriptorHelper::IsSupported(essence_type))
        helper = std::make_unique<MJPEGMXFDescriptorHelper>();
    else
        helper = std::make_unique<PictureMXFDescriptorHelper>();

    helper->SetEssenceType(essence_type);

    return helper;
}

PictureMXFDescriptorHelper::PictureMXFDescriptorHelper()
: MXFDescriptorHelper()
{
    mEssenceType = PICTURE_ESSENCE;
    mAvidResolutionId = 0;
    BMX_OPT_PROP_DEFAULT(mAspectRatio, ASPECT_RATIO_16_9);
    BMX_OPT_PROP_DEFAULT(mAFD, 0);
    BMX_OPT_PROP_DEFAULT(mImageAlignmentOffset, 1);
    BMX_OPT_PROP_DEFAULT(mImageStartOffset, 0);
    BMX_OPT_PROP_DEFAULT(mImageEndOffset, 0);
    BMX_OPT_PROP_DEFAULT(mSignalStandard, MXF_SIGNAL_STANDARD_NONE);
    BMX_OPT_PROP_DEFAULT(mFrameLayout, MXF_FULL_FRAME);
    BMX_OPT_PROP_DEFAULT(mColorSiting, MXF_COLOR_SITING_UNKNOWN);
    BMX_OPT_PROP_DEFAULT(mFieldDominance, 1);
    BMX_OPT_PROP_DEFAULT(mVideoLineMap, g_Null_Video_Line_Map);
    BMX_OPT_PROP_DEFAULT(mBlackRefLevel, 0);
    BMX_OPT_PROP_DEFAULT(mWhiteRefLevel, 0);
    BMX_OPT_PROP_DEFAULT(mColorRange, 0);
    BMX_OPT_PROP_DEFAULT(mComponentMaxRef, 0);
    BMX_OPT_PROP_DEFAULT(mComponentMinRef, 0);
    BMX_OPT_PROP_DEFAULT(mScanningDirection, 0);
    BMX_OPT_PROP_DEFAULT(mTransferCh, g_Null_UL);
    BMX_OPT_PROP_DEFAULT(mCodingEquations, g_Null_UL);
    BMX_OPT_PROP_DEFAULT(mColorPrimaries, g_Null_UL);
    BMX_OPT_PROP_DEFAULT(mMasteringDisplayPrimaries, g_Null_Three_Color_Primaries);
    BMX_OPT_PROP_DEFAULT(mMasteringDisplayWhitePointChromaticity, g_Null_Color_Primary);
    BMX_OPT_PROP_DEFAULT(mMasteringDisplayMaximumLuminance, 0);
    BMX_OPT_PROP_DEFAULT(mMasteringDisplayMinimumLuminance, 0);
    BMX_OPT_PROP_DEFAULT(mActiveWidth, 0);
    BMX_OPT_PROP_DEFAULT(mActiveHeight, 0);
    BMX_OPT_PROP_DEFAULT(mActiveXOffset, 0);
    BMX_OPT_PROP_DEFAULT(mActiveYOffset, 0);
    BMX_OPT_PROP_DEFAULT(mDisplayF2Offset, 0);
    BMX_OPT_PROP_DEFAULT(mAlternativeCenterCuts, vector<mxfUL>());
}

PictureMXFDescriptorHelper::~PictureMXFDescriptorHelper()
{
}

void PictureMXFDescriptorHelper::Initialize(FileDescriptor *file_descriptor, uint16_t mxf_version,
                                            mxfUL alternative_ec_label)
{
    MXFDescriptorHelper::Initialize(file_descriptor, mxf_version, alternative_ec_label);

    GenericPictureEssenceDescriptor *picture_descriptor = dynamic_cast<GenericPictureEssenceDescriptor*>(file_descriptor);
    BMX_ASSERT(picture_descriptor);
    CDCIEssenceDescriptor *cdci_descriptor = dynamic_cast<CDCIEssenceDescriptor*>(picture_descriptor);
    RGBAEssenceDescriptor *rgba_descriptor = dynamic_cast<RGBAEssenceDescriptor*>(picture_descriptor);

    if (picture_descriptor->haveAspectRatio())
        BMX_OPT_PROP_SET(mAspectRatio, picture_descriptor->getAspectRatio());
    if (picture_descriptor->haveActiveFormatDescriptor()) {
        mxfRational afd_aspect_ratio;
        decode_afd(picture_descriptor->getActiveFormatDescriptor(), mxf_version, &mAFD, &afd_aspect_ratio);
        BMX_OPT_PROP_MARK(mAFD, true);
        // the Aspect Ratio property takes precedence over the value encoded in the AFD
        if (!BMX_OPT_PROP_IS_SET(mAspectRatio))
            mAspectRatio = afd_aspect_ratio;
    }
    if (picture_descriptor->haveImageAlignmentOffset())
        BMX_OPT_PROP_SET(mImageAlignmentOffset, picture_descriptor->getImageAlignmentOffset());
    if (picture_descriptor->haveImageStartOffset())
        BMX_OPT_PROP_SET(mImageStartOffset, picture_descriptor->getImageStartOffset());
    if (picture_descriptor->haveImageEndOffset())
        BMX_OPT_PROP_SET(mImageEndOffset, picture_descriptor->getImageEndOffset());
    if (picture_descriptor->haveSignalStandard())
        BMX_OPT_PROP_SET(mSignalStandard, picture_descriptor->getSignalStandard());
    if (picture_descriptor->haveFrameLayout())
        BMX_OPT_PROP_SET(mFrameLayout, picture_descriptor->getFrameLayout());
    if (picture_descriptor->haveFieldDominance())
        BMX_OPT_PROP_SET(mFieldDominance, picture_descriptor->getFieldDominance());
    if (picture_descriptor->haveVideoLineMap())
        BMX_OPT_PROP_SET(mVideoLineMap, picture_descriptor->getVideoLineMapStruct());
    if (picture_descriptor->haveCaptureGamma())
        BMX_OPT_PROP_SET(mTransferCh, picture_descriptor->getCaptureGamma());
    if (picture_descriptor->haveCodingEquations())
        BMX_OPT_PROP_SET(mCodingEquations, picture_descriptor->getCodingEquations());
    if (picture_descriptor->haveColorPrimaries())
        BMX_OPT_PROP_SET(mColorPrimaries, picture_descriptor->getColorPrimaries());

    if (picture_descriptor->haveMasteringDisplayPrimaries())
        BMX_OPT_PROP_SET(mMasteringDisplayPrimaries, picture_descriptor->getMasteringDisplayPrimaries());
    if (picture_descriptor->haveMasteringDisplayWhitePointChromaticity())
        BMX_OPT_PROP_SET(mMasteringDisplayWhitePointChromaticity, picture_descriptor->getMasteringDisplayWhitePointChromaticity());
    if (picture_descriptor->haveMasteringDisplayMaximumLuminance())
        BMX_OPT_PROP_SET(mMasteringDisplayMaximumLuminance, picture_descriptor->getMasteringDisplayMaximumLuminance());
    if (picture_descriptor->haveMasteringDisplayMinimumLuminance())
        BMX_OPT_PROP_SET(mMasteringDisplayMinimumLuminance, picture_descriptor->getMasteringDisplayMinimumLuminance());

    if (picture_descriptor->haveActiveWidth())
        BMX_OPT_PROP_SET(mActiveWidth, picture_descriptor->getActiveWidth());
    if (picture_descriptor->haveActiveHeight())
        BMX_OPT_PROP_SET(mActiveHeight, picture_descriptor->getActiveHeight());
    if (picture_descriptor->haveActiveXOffset())
        BMX_OPT_PROP_SET(mActiveXOffset, picture_descriptor->getActiveXOffset());
    if (picture_descriptor->haveActiveYOffset())
        BMX_OPT_PROP_SET(mActiveYOffset, picture_descriptor->getActiveYOffset());

    if (picture_descriptor->haveDisplayF2Offset() &&
            picture_descriptor->haveFrameLayout() &&
            (picture_descriptor->getFrameLayout() == MXF_SEPARATE_FIELDS ||
             picture_descriptor->getFrameLayout() == MXF_MIXED_FIELDS))
    {
        BMX_OPT_PROP_SET(mDisplayF2Offset, picture_descriptor->getDisplayF2Offset());
    }

    if (picture_descriptor->haveAlternativeCenterCuts())
        BMX_OPT_PROP_SET(mAlternativeCenterCuts, picture_descriptor->getAlternativeCenterCuts());

    if (cdci_descriptor) {
        if (cdci_descriptor->haveColorSiting())
            BMX_OPT_PROP_SET(mColorSiting, cdci_descriptor->getColorSiting());
        if (cdci_descriptor->haveBlackRefLevel())
            BMX_OPT_PROP_SET(mBlackRefLevel, cdci_descriptor->getBlackRefLevel());
        if (cdci_descriptor->haveWhiteReflevel())
            BMX_OPT_PROP_SET(mWhiteRefLevel, cdci_descriptor->getWhiteReflevel());
        if (cdci_descriptor->haveColorRange())
            BMX_OPT_PROP_SET(mColorRange, cdci_descriptor->getColorRange());
    }
    if (rgba_descriptor) {
        if (rgba_descriptor->haveComponentMaxRef())
            BMX_OPT_PROP_SET(mComponentMaxRef, rgba_descriptor->getComponentMaxRef());
        if (rgba_descriptor->haveComponentMinRef())
            BMX_OPT_PROP_SET(mComponentMinRef, rgba_descriptor->getComponentMinRef());
        if (rgba_descriptor->haveScanningDirection())
            BMX_OPT_PROP_SET(mScanningDirection, rgba_descriptor->getScanningDirection());
    }
}

void PictureMXFDescriptorHelper::SetAspectRatio(mxfRational aspect_ratio)
{
    BMX_OPT_PROP_SET(mAspectRatio, aspect_ratio);
}

void PictureMXFDescriptorHelper::SetAFD(uint8_t afd)
{
    BMX_OPT_PROP_SET(mAFD, afd);
}

void PictureMXFDescriptorHelper::SetSignalStandard(MXFSignalStandard signal_standard)
{
    BMX_OPT_PROP_SET(mSignalStandard, signal_standard);
}

void PictureMXFDescriptorHelper::SetFrameLayout(MXFFrameLayout frame_layout)
{
    BMX_OPT_PROP_SET(mFrameLayout, frame_layout);
}

void PictureMXFDescriptorHelper::SetFieldDominance(uint8_t field_num)
{
    BMX_OPT_PROP_SET(mFieldDominance, field_num);
}

void PictureMXFDescriptorHelper::SetVideoLineMap(int32_t first, int32_t second)
{
    mxfVideoLineMap value = {first, second};
    BMX_OPT_PROP_SET(mVideoLineMap, value);
}

void PictureMXFDescriptorHelper::SetVideoLineMap(mxfVideoLineMap video_line_map)
{
    BMX_OPT_PROP_SET(mVideoLineMap, video_line_map);
}

void PictureMXFDescriptorHelper::SetTransferCharacteristic(mxfUL label)
{
    BMX_OPT_PROP_SET(mTransferCh, label);
}

void PictureMXFDescriptorHelper::SetCodingEquations(mxfUL label)
{
    BMX_OPT_PROP_SET(mCodingEquations, label);
}

void PictureMXFDescriptorHelper::SetColorPrimaries(mxfUL label)
{
    BMX_OPT_PROP_SET(mColorPrimaries, label);
}

void PictureMXFDescriptorHelper::SetColorSiting(MXFColorSiting color_siting)
{
    BMX_OPT_PROP_SET(mColorSiting, color_siting);
}

void PictureMXFDescriptorHelper::SetBlackRefLevel(uint32_t level)
{
    BMX_OPT_PROP_SET(mBlackRefLevel, level);
}

void PictureMXFDescriptorHelper::SetWhiteRefLevel(uint32_t level)
{
    BMX_OPT_PROP_SET(mWhiteRefLevel, level);
}

void PictureMXFDescriptorHelper::SetColorRange(uint32_t range)
{
    BMX_OPT_PROP_SET(mColorRange, range);
}

void PictureMXFDescriptorHelper::SetComponentMaxRef(uint32_t ref)
{
    BMX_OPT_PROP_SET(mComponentMaxRef, ref);
}

void PictureMXFDescriptorHelper::SetComponentMinRef(uint32_t ref)
{
    BMX_OPT_PROP_SET(mComponentMinRef, ref);
}

void PictureMXFDescriptorHelper::SetScanningDirection(uint8_t direction)
{
    BMX_OPT_PROP_SET(mScanningDirection, direction);
}

void PictureMXFDescriptorHelper::SetMasteringDisplayPrimaries(mxfThreeColorPrimaries primaries)
{
    BMX_OPT_PROP_SET(mMasteringDisplayPrimaries, primaries);
}

void PictureMXFDescriptorHelper::SetMasteringDisplayWhitePointChromaticity(mxfColorPrimary chroma)
{
    BMX_OPT_PROP_SET(mMasteringDisplayWhitePointChromaticity, chroma);
}

void PictureMXFDescriptorHelper::SetMasteringDisplayMaximumLuminance(uint32_t max_lum)
{
    BMX_OPT_PROP_SET(mMasteringDisplayMaximumLuminance, max_lum);
}

void PictureMXFDescriptorHelper::SetMasteringDisplayMinimumLuminance(uint32_t min_lum)
{
    BMX_OPT_PROP_SET(mMasteringDisplayMinimumLuminance, min_lum);
}

void PictureMXFDescriptorHelper::SetActiveWidth(uint32_t width)
{
    BMX_OPT_PROP_SET(mActiveWidth, width);
}

void PictureMXFDescriptorHelper::SetActiveHeight(uint32_t height)
{
    BMX_OPT_PROP_SET(mActiveHeight, height);
}

void PictureMXFDescriptorHelper::SetActiveXOffset(uint32_t offset)
{
    BMX_OPT_PROP_SET(mActiveXOffset, offset);
}

void PictureMXFDescriptorHelper::SetActiveYOffset(uint32_t offset)
{
    BMX_OPT_PROP_SET(mActiveYOffset, offset);
}

void PictureMXFDescriptorHelper::SetDisplayF2Offset(int32_t offset)
{
    BMX_OPT_PROP_SET(mDisplayF2Offset, offset);
}

void PictureMXFDescriptorHelper::SetAlternativeCenterCuts(vector<mxfUL> &cuts)
{
    BMX_OPT_PROP_SET(mAlternativeCenterCuts, cuts);
}

FileDescriptor* PictureMXFDescriptorHelper::CreateFileDescriptor(HeaderMetadata *header_metadata)
{
    (void)header_metadata;

    // implemented by child classes only
    BMX_ASSERT(false);
    return 0;
}

void PictureMXFDescriptorHelper::UpdateFileDescriptor()
{
    MXFDescriptorHelper::UpdateFileDescriptor();

    GenericPictureEssenceDescriptor *picture_descriptor = dynamic_cast<GenericPictureEssenceDescriptor*>(mFileDescriptor);
    BMX_ASSERT(picture_descriptor);
    CDCIEssenceDescriptor *cdci_descriptor = dynamic_cast<CDCIEssenceDescriptor*>(mFileDescriptor);
    RGBAEssenceDescriptor *rgba_descriptor = dynamic_cast<RGBAEssenceDescriptor*>(mFileDescriptor);

    picture_descriptor->setAspectRatio(mAspectRatio);
    // TODO: what should be done if the source AFD value's aspect ratio != mAspectRatio?
    if (BMX_OPT_PROP_IS_SET(mAFD))
        picture_descriptor->setActiveFormatDescriptor(encode_afd(mAFD, mAspectRatio));
    if (BMX_OPT_PROP_IS_SET(mSignalStandard))
        picture_descriptor->setSignalStandard(mSignalStandard);
    if (BMX_OPT_PROP_IS_SET(mFrameLayout))
        picture_descriptor->setFrameLayout(mFrameLayout);
    if (BMX_OPT_PROP_IS_SET(mFieldDominance))
        picture_descriptor->setFieldDominance(mFieldDominance);
    if (BMX_OPT_PROP_IS_SET(mVideoLineMap))
        picture_descriptor->setVideoLineMap(mVideoLineMap);
    if (BMX_OPT_PROP_IS_SET(mTransferCh))
        picture_descriptor->setCaptureGamma(mTransferCh);
    if (BMX_OPT_PROP_IS_SET(mCodingEquations))
        SetCodingEquationsMod(mCodingEquations);
    if (BMX_OPT_PROP_IS_SET(mColorPrimaries))
        picture_descriptor->setColorPrimaries(mColorPrimaries);

    if (BMX_OPT_PROP_IS_SET(mMasteringDisplayPrimaries))
        picture_descriptor->setMasteringDisplayPrimaries(mMasteringDisplayPrimaries);
    if (BMX_OPT_PROP_IS_SET(mMasteringDisplayWhitePointChromaticity))
        picture_descriptor->setMasteringDisplayWhitePointChromaticity(mMasteringDisplayWhitePointChromaticity);
    if (BMX_OPT_PROP_IS_SET(mMasteringDisplayMaximumLuminance))
        picture_descriptor->setMasteringDisplayMaximumLuminance(mMasteringDisplayMaximumLuminance);
    if (BMX_OPT_PROP_IS_SET(mMasteringDisplayMinimumLuminance))
        picture_descriptor->setMasteringDisplayMinimumLuminance(mMasteringDisplayMinimumLuminance);

    if (BMX_OPT_PROP_IS_SET(mActiveWidth))
        picture_descriptor->setActiveWidth(mActiveWidth);
    if (BMX_OPT_PROP_IS_SET(mActiveHeight))
        picture_descriptor->setActiveHeight(mActiveHeight);
    if (BMX_OPT_PROP_IS_SET(mActiveXOffset))
        picture_descriptor->setActiveXOffset(mActiveXOffset);
    if (BMX_OPT_PROP_IS_SET(mActiveYOffset))
        picture_descriptor->setActiveYOffset(mActiveYOffset);

    if (BMX_OPT_PROP_IS_SET(mDisplayF2Offset))
        picture_descriptor->setDisplayF2Offset(mDisplayF2Offset);

    if (BMX_OPT_PROP_IS_SET(mAlternativeCenterCuts))
        picture_descriptor->setAlternativeCenterCuts(mAlternativeCenterCuts);

    if (cdci_descriptor) {
        if (BMX_OPT_PROP_IS_SET(mColorSiting))
            SetColorSitingMod(mColorSiting);
        if (BMX_OPT_PROP_IS_SET(mBlackRefLevel))
            cdci_descriptor->setBlackRefLevel(mBlackRefLevel);
        if (BMX_OPT_PROP_IS_SET(mWhiteRefLevel))
            cdci_descriptor->setWhiteReflevel(mWhiteRefLevel);
        if (BMX_OPT_PROP_IS_SET(mColorRange))
            cdci_descriptor->setColorRange(mColorRange);
    }
    if (rgba_descriptor) {
        if (BMX_OPT_PROP_IS_SET(mComponentMaxRef))
            rgba_descriptor->setComponentMaxRef(mComponentMaxRef);
        if (BMX_OPT_PROP_IS_SET(mComponentMinRef))
            rgba_descriptor->setComponentMinRef(mComponentMinRef);
        if (BMX_OPT_PROP_IS_SET(mScanningDirection))
            rgba_descriptor->setScanningDirection(mScanningDirection);
    }

    if ((mFlavour & MXFDESC_AVID_FLAVOUR)) {
        if (GetImageAlignmentOffset() > 1)
            picture_descriptor->setImageAlignmentOffset(GetImageAlignmentOffset());
        if (GetImageStartOffset() > 0)
            picture_descriptor->setImageStartOffset(GetImageStartOffset());
        // not setting ImageEndOffset because Avid alpha channel sample files did not have it set
        SetAvidFrameSampleSize(GetEditUnitSize());
        if (mAvidResolutionId != 0)
            SetAvidResolutionID(mAvidResolutionId);
    }
}

bool PictureMXFDescriptorHelper::HaveAvidResolutionID()
{
    BMX_ASSERT(mFileDescriptor);
    return mFileDescriptor->haveItem(&MXF_ITEM_K(GenericPictureEssenceDescriptor, ResolutionID));
}

int32_t PictureMXFDescriptorHelper::GetAvidResolutionID()
{
    BMX_ASSERT(mFileDescriptor);
    return mFileDescriptor->getInt32Item(&MXF_ITEM_K(GenericPictureEssenceDescriptor, ResolutionID));
}

void PictureMXFDescriptorHelper::SetAvidResolutionID(int32_t resolution_id)
{
    BMX_ASSERT(mFileDescriptor);
    return mFileDescriptor->setInt32Item(&MXF_ITEM_K(GenericPictureEssenceDescriptor, ResolutionID), resolution_id);
}

bool PictureMXFDescriptorHelper::HaveAvidFrameSampleSize()
{
    BMX_ASSERT(mFileDescriptor);
    return mFileDescriptor->haveItem(&MXF_ITEM_K(GenericPictureEssenceDescriptor, FrameSampleSize));
}

int32_t PictureMXFDescriptorHelper::GetAvidFrameSampleSize()
{
    BMX_ASSERT(mFileDescriptor);
    return mFileDescriptor->getInt32Item(&MXF_ITEM_K(GenericPictureEssenceDescriptor, FrameSampleSize));
}

void PictureMXFDescriptorHelper::SetAvidFrameSampleSize(int32_t size)
{
    BMX_ASSERT(mFileDescriptor);
    return mFileDescriptor->setInt32Item(&MXF_ITEM_K(GenericPictureEssenceDescriptor, FrameSampleSize), size);
}

bool PictureMXFDescriptorHelper::HaveAvidImageSize()
{
    BMX_ASSERT(mFileDescriptor);
    return mFileDescriptor->haveItem(&MXF_ITEM_K(GenericPictureEssenceDescriptor, ImageSize));
}

int32_t PictureMXFDescriptorHelper::GetAvidImageSize()
{
    BMX_ASSERT(mFileDescriptor);
    return mFileDescriptor->getInt32Item(&MXF_ITEM_K(GenericPictureEssenceDescriptor, ImageSize));
}

void PictureMXFDescriptorHelper::SetAvidImageSize(int32_t size)
{
    BMX_ASSERT(mFileDescriptor);
    return mFileDescriptor->setInt32Item(&MXF_ITEM_K(GenericPictureEssenceDescriptor, ImageSize), size);
}

bool PictureMXFDescriptorHelper::HaveAvidFirstFrameOffset()
{
    BMX_ASSERT(mFileDescriptor);
    return mFileDescriptor->haveItem(&MXF_ITEM_K(GenericPictureEssenceDescriptor, FirstFrameOffset));
}

int32_t PictureMXFDescriptorHelper::GetAvidFirstFrameOffset()
{
    BMX_ASSERT(mFileDescriptor);
    return mFileDescriptor->getInt32Item(&MXF_ITEM_K(GenericPictureEssenceDescriptor, FirstFrameOffset));
}

void PictureMXFDescriptorHelper::SetFirstFrameOffset(int32_t offset)
{
    BMX_ASSERT(mFileDescriptor);
    return mFileDescriptor->setInt32Item(&MXF_ITEM_K(GenericPictureEssenceDescriptor, FirstFrameOffset), offset);
}

mxfUL PictureMXFDescriptorHelper::ChooseEssenceContainerUL() const
{
    // implemented by child classes only
    BMX_ASSERT(false);
    return g_Null_UL;
}

void PictureMXFDescriptorHelper::SetCodingEquationsMod(mxfUL label)
{
    GenericPictureEssenceDescriptor *picture_descriptor = dynamic_cast<GenericPictureEssenceDescriptor*>(mFileDescriptor);
    BMX_ASSERT(picture_descriptor);

    mxfAUID auid;
    if ((mFlavour & MXFDESC_AVID_FLAVOUR)) {
        // this label is half-swapped in Avid files
        // Note that 377-1 defines an AUID with a UL stored as-is and an UUID half swapped. An IDAU has the
        // opposite, swapping the UL. The "AUID" (aafUID_t) type defined in the AAF SDK is therefore an IDAU! The
        // mxfAUID type and mxf_avid_set_auid function follow the AAF SDK naming
        mxf_avid_set_auid(&label, &auid);
        picture_descriptor->setCodingEquations(auid);
    } else {
        picture_descriptor->setCodingEquations(label);
    }
}

void PictureMXFDescriptorHelper::SetColorSitingMod(uint8_t color_siting)
{
    CDCIEssenceDescriptor *cdci_descriptor = dynamic_cast<CDCIEssenceDescriptor*>(mFileDescriptor);
    BMX_ASSERT(cdci_descriptor);

    if ((mFlavour & MXFDESC_SMPTE_377_2004_FLAVOUR)) {
        if (color_siting > MXF_COLOR_SITING_REC601)
            cdci_descriptor->setColorSiting(MXF_COLOR_SITING_UNKNOWN);
        else
            cdci_descriptor->setColorSiting(color_siting);
    } else {
        // MXF_COLOR_SITING_VERT_MIDPOINT is 2nd of 2 additional color siting enums added in SMPTE 377-1
        if (color_siting > MXF_COLOR_SITING_VERT_MIDPOINT)
            cdci_descriptor->setColorSiting(MXF_COLOR_SITING_UNKNOWN);
        else
            cdci_descriptor->setColorSiting(color_siting);
    }
}
