#ifndef CONTENTTYPE_H_INCLUDED
#define CONTENTTYPE_H_INCLUDED


#include <string>


namespace HSServer {


    enum ContentType
    {
        ContentType_Unknown,
        ContentType_Begin,
        ContentType_TextPlain = ContentType_Begin,
        ContentType_TextHTML,
        ContentType_ApplicationXML,
        ContentType_End
    };

    /**
     * Returns the string representation of the requested content type.
     *
     * For example:
     *   ContentType_TextPlain => "text/plain"
     *   ContentType_TextHTML => "text/html"
     *   ...
     */
    const char * ToString(ContentType inRequestMethod);

    bool FromString(const std::string & inText, ContentType & outRequestMethod);

    
    template<ContentType _ContentType>
    class ContentTypePolicy
    {
    public:
        static ContentType GetContentType() { return _ContentType; }
    };


} // namespace HSServer


#endif // CONTENTTYPE_H_INCLUDED
