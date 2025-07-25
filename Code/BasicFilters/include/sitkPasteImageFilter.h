/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef sitkPasteImageFilter_h
#define sitkPasteImageFilter_h

/*
 * WARNING: DO NOT EDIT THIS FILE!
 * THIS FILE IS AUTOMATICALLY GENERATED BY THE SIMPLEITK BUILD PROCESS.
 * Please look at sitkImageFilterTemplate.h.in to make changes.
 */

#include <memory>

#include "sitkBasicFilters.h"
#include "sitkImageFilter.h"

namespace itk::simple
{

/** \class PasteImageFilter
 * \brief Paste an image (or a constant value) into another image.
 *
 * PasteImageFilter allows a region in a destination image to be filled with a source image or a constant pixel value.
 * The SetDestinationIndex() method
 * prescribes where in the destination input to start pasting data from the
 * source input.  The SetSourceRegion method prescribes the section of
 * the second image to paste into the first. When a constant pixel value is set, the SourceRegion describes the size
 * of the region filled. If the output requested
 * region does not include the SourceRegion after it has been
 * repositioned to DestinationIndex, then the output will just be
 * a copy of the input.
 *
 * This filter supports running "InPlace" to efficiently reuses the destination image buffer for the output, removing
 * the need to copy the destination pixels to the output.
 *
 * When the source image is a lower dimension than the destination image then the DestinationSkipAxes parameter
 * specifies which axes in the destination image are set to 1 when copying the region or filling with a constant.
 *
 */
class SITKBasicFilters_EXPORT PasteImageFilter : public ImageFilter
{
public:
  using Self = PasteImageFilter;

  /** Destructor */
  virtual ~PasteImageFilter();

  /** Default Constructor that takes no arguments and initializes
   * default parameters */
  PasteImageFilter();

  /** Define the pixels types supported by this filter */
  using PixelIDTypeList = NonLabelPixelIDTypeList;


  /**
   */
  void
  SetSourceSize(std::vector<unsigned int> SourceSize)
  {
    this->m_SourceSize = std::move(SourceSize);
  }

  /**
   */
  std::vector<unsigned int>
  GetSourceSize() const
  {
    return this->m_SourceSize;
  }

  /**
   */
  void
  SetSourceIndex(std::vector<int> SourceIndex)
  {
    this->m_SourceIndex = std::move(SourceIndex);
  }

  /**
   */
  std::vector<int>
  GetSourceIndex() const
  {
    return this->m_SourceIndex;
  }

  /**
   * Set/Get the destination index (where in the first input the second input will be pasted.
   */
  void
  SetDestinationIndex(std::vector<int> DestinationIndex)
  {
    this->m_DestinationIndex = std::move(DestinationIndex);
  }

  /**
   * Set/Get the destination index (where in the first input the second input will be pasted.
   */
  std::vector<int>
  GetDestinationIndex() const
  {
    return this->m_DestinationIndex;
  }


  /** Set/Get the array describing which axes in the destination image to skip
   *
   * The axes with true values are set to 1, to fill the difference between the dimension of the input and source image.
   * The number of true value in DestinationSkipAxes plus the DestinationImageDimension must equal the
   * InputImageDimension.
   *
   * By default this array contains SourceImageDimension false values followed by true values for the remainder.
   */
  void
  SetDestinationSkipAxes(std::vector<bool> DestinationSkipAxes)
  {
    this->m_DestinationSkipAxes = std::move(DestinationSkipAxes);
  }

  /** Set/Get the array describing which axes in the destination image to skip
   *
   * The axes with true values are set to 1, to fill the difference between the dimension of the input and source image.
   * The number of true values in DestinationSkipAxes plus the DestinationImageDimension must equal the
   * InputImageDimension.
   *
   * By default this array contains SourceImageDimension false values followed by true values for the remainder.
   */
  std::vector<bool>
  GetDestinationSkipAxes() const
  {
    return this->m_DestinationSkipAxes;
  }


  /** Name of this class */
  std::string
  GetName() const
  {
    return std::string("PasteImageFilter");
  }

  /** Print ourselves out */
  std::string
  ToString() const;


  /** Execute the filter on the input image */
#ifndef SWIG
  Image
  Execute(Image && destinationImage, const Image & sourceImage);
  Image
  Execute(Image && destinationImage, double constant);
#endif
  Image
  Execute(const Image & destinationImage, const Image & sourceImage);
  Image
  Execute(const Image & destinationImage, double constant);


private:
  /** Setup for member function dispatching */

  using MemberFunctionType = Image (Self::*)(const Image * destinationImage, const Image * sourceImage);
  template <class TImageType>
  Image
  ExecuteInternal(const Image * destinationImage, const Image * sourceImage);

  template <class TImageType, unsigned int OutputDimension>
  Image
  ExecuteInternal(const TImageType *                                    destinationImage,
                  const Image *                                         sourceImage,
                  std::integral_constant<unsigned int, OutputDimension> meta);
  template <class TImageType>
  Image
  ExecuteInternal(const TImageType *                      destinationImage,
                  const Image *                           sourceImage,
                  std::integral_constant<unsigned int, 1> meta);
  template <class TImageType>
  Image
  ExecuteInternal(const Image * image, double constant);


  friend struct detail::MemberFunctionAddressor<MemberFunctionType>;

  using MemberFunction2Type = Image (Self::*)(const Image * image, double constant);


  friend struct detail::MemberFunctionAddressor<MemberFunction2Type>;

  static const detail::MemberFunctionFactory<MemberFunctionType> &
  GetMemberFunctionFactory();
  static const detail::MemberFunctionFactory<MemberFunction2Type> &
  GetMemberFunctionFactory2();


  std::vector<unsigned int> m_SourceSize{ std::vector<unsigned int>(SITK_MAX_DIMENSION, 1) };

  std::vector<int> m_SourceIndex{ std::vector<int>(SITK_MAX_DIMENSION, 0) };

  std::vector<int> m_DestinationIndex{ std::vector<int>(SITK_MAX_DIMENSION, 0) };

  std::vector<bool> m_DestinationSkipAxes{};

  bool m_InPlace{ false };
};

/**\
 * \brief Paste an image into another image.
 *
 * This function directly calls the execute method of PasteImageFilter
 * in order to support a procedural API
 *
 * \sa itk::simple::PasteImageFilter for the object oriented interface
 * @{
 */
#ifndef SWIG
SITKBasicFilters_EXPORT Image
Paste(Image &&                  destinationImage,
      const Image &             sourceImage,
      std::vector<unsigned int> sourceSize = std::vector<unsigned int>(SITK_MAX_DIMENSION, 1),
      std::vector<int>          sourceIndex = std::vector<int>(SITK_MAX_DIMENSION, 0),
      std::vector<int>          destinationIndex = std::vector<int>(SITK_MAX_DIMENSION, 0),
      std::vector<bool>         DestinationSkipAxes = std::vector<bool>());
#endif
SITKBasicFilters_EXPORT Image
Paste(const Image &             destinationImage,
      const Image &             sourceImage,
      std::vector<unsigned int> sourceSize = std::vector<unsigned int>(SITK_MAX_DIMENSION, 1),
      std::vector<int>          sourceIndex = std::vector<int>(SITK_MAX_DIMENSION, 0),
      std::vector<int>          destinationIndex = std::vector<int>(SITK_MAX_DIMENSION, 0),
      std::vector<bool>         DestinationSkipAxes = std::vector<bool>());

/** @} */
} // namespace itk::simple
#endif
