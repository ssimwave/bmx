/*
 * Copyright (C) 2017, British Broadcasting Corporation
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

#include <bmx/mxf_op1a/OP1ARDD36Track.h>
#include <bmx/mxf_op1a/OP1AFile.h>
#include <bmx/essence_parser/RDD36EssenceParser.h>
#include <bmx/BMXException.h>
#include <bmx/Logging.h>

using namespace std;
using namespace bmx;
using namespace mxfpp;



static const mxfKey VIDEO_ELEMENT_KEY = MXF_RDD36_EE_K(0x01, MXF_RDD36_FRAME_WRAPPED_EE_TYPE, 0x00);



OP1ARDD36Track::OP1ARDD36Track(OP1AFile *file, uint32_t track_index, uint32_t track_id, uint8_t track_type_number,
                               mxfRational frame_rate, EssenceType essence_type)
: OP1APictureTrack(file, track_index, track_id, track_type_number, frame_rate, essence_type)
{
    mRDD36DescriptorHelper = dynamic_cast<RDD36MXFDescriptorHelper*>(GetMXFDescriptorHelper());
    BMX_ASSERT(mRDD36DescriptorHelper);

    mRDD36DescriptorHelper->SetComponentDepth(10);

    mTrackNumber = MXF_RDD36_TRACK_NUM(0x01, MXF_RDD36_FRAME_WRAPPED_EE_TYPE, 0x00);
    mEssenceElementKey = VIDEO_ELEMENT_KEY;

    mPosition = 0;
}

OP1ARDD36Track::~OP1ARDD36Track()
{
}

void OP1ARDD36Track::SetComponentDepth(uint32_t depth)
{
    mRDD36DescriptorHelper->SetComponentDepth(depth);
}

void OP1ARDD36Track::PrepareWrite(uint8_t track_count)
{
    CompleteEssenceKeyAndTrackNum(track_count);

    mCPManager->RegisterPictureTrackElement(mTrackIndex, mEssenceElementKey, false, 5);
    mIndexTable->RegisterPictureTrackElement(mTrackIndex, false, false);
}

void OP1ARDD36Track::WriteSamplesInt(const unsigned char *data, uint32_t size, uint32_t num_samples)
{
    if (mPosition == 0) {
        RDD36EssenceParser essence_parser;
        essence_parser.ParseFrameInfo(data, size);
        mRDD36DescriptorHelper->UpdateFileDescriptor(&essence_parser);
    }

    mCPManager->WriteSamples(mTrackIndex, data, size, num_samples);
    mIndexTable->AddIndexEntry(mTrackIndex, mPosition, 0, 0, 0, true, false);

    mPosition++;
}
