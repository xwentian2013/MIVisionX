#pragma  once
#include <memory>
#include "reader.h"
#include "decoder.h"
#include "commons.h"
#include "image.h"




enum class LoaderModuleStatus
{
    OK = 0,
    DEVICE_BUFFER_SWAP_FAILED,
    HOST_BUFFER_SWAP_FAILED,
    NO_FILES_TO_READ,
    DECODE_FAILED,
    NO_MORE_DATA_TO_READ,
    NOT_INITIALIZED
};

/*! \class LoaderModule The interface defining the API and requirements of loader modules*/
class LoaderModule 
{
public:
    virtual void initialize(ReaderConfig reader_config, DecoderConfig decoder_config, RaliMemType mem_type, unsigned batch_size) = 0;
    virtual void set_output_image(Image* output_image) = 0;
    virtual LoaderModuleStatus load_next() = 0; // Loads the next image data into the Image's buffer set by calling into the set_output_image
    virtual void reset() = 0; // Resets the loader to load from the beginning of the media
    virtual size_t count() = 0; // Returns the number of available images to be loaded
    virtual ~LoaderModule()= default;
    virtual std::vector<long long unsigned> timing() = 0;// Returns timing info
    virtual void stop() = 0; // stop the internal process of loading (if any)
};

using pLoaderModule = std::shared_ptr<LoaderModule>;