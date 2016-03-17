function TemplateRegistry(){

    var templates = {};

    this.load = function(){
        var registry = this;
        $("script[type='text/template']").each(function(){
            var name = $(this).attr("id").replace(/_tpl/, "");
            registry.register(name, $(this).html());
        });
        return true;
    };

    this.register = function(name, content){
        templates[name] = (content instanceof Function) ? content : _.template(content);

        return true;
    };

    this.get = function(name){
        return templates[name];
    };

    return this;
}

