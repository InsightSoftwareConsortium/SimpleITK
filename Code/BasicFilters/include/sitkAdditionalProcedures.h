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
#ifndef sitkAdditionalProcedures_h
#define sitkAdditionalProcedures_h


#include "sitkBasicFilters.h"
#include "sitkImage.h"
#include "sitkTransform.h"
#include "sitkInterpolator.h"
#include "sitkPatchBasedDenoisingImageFilter.h"

namespace itk::simple
{


/**
 * \brief itk::simple::ResampleImageFilter Procedural Interface
 *
 * These functions call the execute method of ResampleImageFilter
 * in order to support a procedural API.
 *
 * The difference between the three functions is in the way the output
 * image's domain parameters are specified (origin, spacing,
 * direction). The first function uses the parameters from the input image,
 * the second uses the parameters of a reference image, and the third uses
 * explicitly specified parameters.
 *
 * \sa itk::simple::ResampleImageFilter for the object oriented interface
 * @{
 */
SITKBasicFilters_EXPORT Image
Resample(const Image &    image1,
         Transform        transform = itk::simple::Transform(),
         InterpolatorEnum interpolator = itk::simple::sitkLinear,
         double           defaultPixelValue = 0.0,
         PixelIDValueEnum outputPixelType = sitkUnknown,
         bool             useNearestNeighborExtrapolator = false);

SITKBasicFilters_EXPORT Image
Resample(const Image &    image1,
         const Image &    referenceImage,
         Transform        transform = itk::simple::Transform(),
         InterpolatorEnum interpolator = itk::simple::sitkLinear,
         double           defaultPixelValue = 0.0,
         PixelIDValueEnum outputPixelType = sitkUnknown,
         bool             useNearestNeighborExtrapolator = false);

SITKBasicFilters_EXPORT Image
Resample(const Image &                 image1,
         const std::vector<uint32_t> & size,
         Transform                     transform = itk::simple::Transform(),
         InterpolatorEnum              interpolator = itk::simple::sitkLinear,
         const std::vector<double> &   outputOrigin = std::vector<double>(3, 0.0),
         const std::vector<double> &   outputSpacing = std::vector<double>(3, 1.0),
         const std::vector<double> &   outputDirection = std::vector<double>(),
         double                        defaultPixelValue = 0.0,
         PixelIDValueEnum              outputPixelType = sitkUnknown,
         bool                          useNearestNeighborExtrapolator = false);
/**@}*/


/**
 * \brief itk::simple::PatchBasedDenoisingImageFilter Procedural Interface
 *
 * This function directly calls the execute method of PatchBasedDenoisingImageFilter
 * in order to support a procedural API
 *
 * \sa itk::simple::PatchBasedDenoisingImageFilter for the object oriented interface
 */
SITKBasicFilters_EXPORT Image
PatchBasedDenoising(const Image &                                               image1,
                    itk::simple::PatchBasedDenoisingImageFilter::NoiseModelType noiseModel,
                    double                                                      kernelBandwidthSigma = 400.0,
                    uint32_t                                                    patchRadius = 4u,
                    uint32_t                                                    numberOfIterations = 1u,
                    uint32_t                                                    numberOfSamplePatches = 200u,
                    double                                                      sampleVariance = 400.0,
                    double                                                      noiseSigma = 0.0,
                    double                                                      noiseModelFidelityWeight = 0.0);

// Disable for certain wrapped languages due to overload shadowing
#if !defined(SWIGLUA)

SITKBasicFilters_EXPORT Image
PatchBasedDenoising(const Image & image1,
                    double        kernelBandwidthSigma = 400.0,
                    uint32_t      patchRadius = 4u,
                    uint32_t      numberOfIterations = 1u,
                    uint32_t      numberOfSamplePatches = 200u,
                    double        sampleVariance = 400.0);
#endif


/**
 * \brief Blurs an image by separable convolution with discrete
 * gaussian kernels. This filter performs Gaussian blurring by
 * separable convolution of an image and a discrete Gaussian
 * operator (kernel).
 *
 * This function directly calls the execute method of DiscreteGaussianImageFilter
 * in order to support a procedural API
 *
 * \sa itk::simple::DiscreteGaussianImageFilter for the object oriented interface
 */
SITKBasicFilters_EXPORT Image
DiscreteGaussian(const Image & image1,
                 double        variance,
                 unsigned int  maximumKernelWidth = 32u,
                 double        maximumError = 0.01,
                 bool          useImageSpacing = true);


/**
 * \brief Computes the smoothing of an image by convolution with
 * the Gaussian kernels implemented as IIR filters.
 *
 * This function directly calls the execute method of SmoothingRecursiveGaussianImageFilter
 * in order to support a procedural API
 *
 * \sa itk::simple::SmoothingRecursiveGaussianImageFilter for the object oriented interface
 */
SITKBasicFilters_EXPORT Image
SmoothingRecursiveGaussian(const Image & image1, double sigma, bool normalizeAcrossScale = false);

} // namespace itk::simple
#endif
