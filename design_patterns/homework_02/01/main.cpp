#include <iostream>
#include <memory>
#include <algorithm>
#include <string>


class IRenderer
{
    public:

        virtual ~IRenderer() = default;
        virtual void render(const std::string& string) const = 0;
};

class ConsoleRenderer : public IRenderer
{
    public:

        void render(const std::string& string) const override
        {
            std::cout << string;
        }
};

class TextDecorator : public IRenderer
{
    protected:

        std::unique_ptr<IRenderer> output_;

    public:

        explicit TextDecorator(std::unique_ptr<IRenderer> output) : output_(std::move(output))
        {
        }

};

class HtmlBoldText : public TextDecorator
{
    public:

        explicit HtmlBoldText(std::unique_ptr<IRenderer> output) : TextDecorator(std::move(output))
        {
        }

        void render(const std::string& string) const override
        {
            std::cout << "<b>";
            output_->render(string);
            std::cout << "</b>";
        }
};

class HtmlItalicText : public TextDecorator
{
    public:

        explicit HtmlItalicText(std::unique_ptr<IRenderer> output) : TextDecorator(std::move(output))
        {
        }

        void render(const std::string& string) const override
        {
            std::cout << "<i>";
            output_->render(string);
            std::cout << "</i>";
        }
};

class TextReverse : public TextDecorator
{
    public:

        explicit TextReverse(std::unique_ptr<IRenderer> output) : TextDecorator(std::move(output))
        {
        }

        void render(const std::string& string) const override
        {
            std::string string_copy { string };

            std::reverse(string_copy.begin(), string_copy.end());

            output_->render(string_copy);
        }
};

class HtmlLink
{
    private:

        std::unique_ptr<IRenderer> output_;

    public:

        explicit HtmlLink(std::unique_ptr<IRenderer> output) : output_(std::move(output))
        {
        }

        void render(const std::string& href, const std::string& text) const
        {
            std::cout << "<a href=\"";
            output_->render(href);
            std::cout << "\">";
            output_->render(text);
            std::cout << "</a>";
        }
};


int main()
{
    std::string text {"Hello world"}, href {"netology.ru"};

    auto text_block
    {
        std::make_unique<HtmlItalicText>(
            std::make_unique<HtmlBoldText>(
                std::make_unique<ConsoleRenderer>()
            )
        )
    };

    text_block->render(text);

    std::cout << '\n';

    auto reverse_text_block
    {
        std::make_unique<TextReverse>(
            std::make_unique<ConsoleRenderer>()
        )
    };

    reverse_text_block->render(text);

    std::cout << '\n';
    
    auto link_block
    {
        std::make_unique<HtmlLink>(
            std::make_unique<ConsoleRenderer>()
        )
    };

    link_block->render(href, text);

    std::cout << '\n';

    return 0;
}