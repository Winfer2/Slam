#ifndef AVR_IO_IMAGE_STREAM_HPP
#define AVR_IO_IMAGE_STREAM_HPP

#include <Core/Core.hpp>

namespace avr {
// TODO: Receber parâmetros intrínsecos (K + distortion lens)
// para corrigir a imagem na leitura

class ImageStream {
public:
   virtual ~ImageStream() {/* dtor */}

   //! Grab a new frame
   ImageStream& operator >> (Image& frame) {
      this->NextFrame(frame);
      return * this;
   }

   //! Initialize the stream
   //! @param config configuration string (see especification for details)
   bool operator () (const string& config) {
      bool loaded;
      this->LoadStream(config, loaded);
      return loaded;
   }

   bool operator! () const { return !this->hasNext(); }
   operator bool() const { return this->hasNext(); }

protected:
   virtual bool hasNext() const = 0;
   virtual void NextFrame(Image&) = 0;
   virtual void LoadStream(const string&, bool&) = 0;
};

} // avr

#endif // AVR_IO_IMAGE_STREAM_HPP
