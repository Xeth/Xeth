
function parseDecimals(value){
    return Math.ceil(((value < 1.0) ? value : (value % Math.floor(value))) * 100000000);
}

function shortify(value, length){
    if(length==undefined){
        length = 57;
    }
    value = ""+value;
    if(value.length <= length){
        return value;
    }
    var half = Math.round((length-3)/2);
    var short = value.substr(0,half)+"..."+value.substr(value.length-half, value.length);
    return short;
}


var CheckBoxView = Backbone.View.extend({
    initialize:function(){
        _(this).bindAll("toggle","disable","enable");
        this.enabled = false;
        this.enable();
    },
    toggle:function(){
        this.$el.toggleClass("on");
        this.trigger("change",this.$el.hasClass("on"));
    },
    val: function(){
        return this.$el.hasClass("on");
    },
    disable:function(){
        if(!this.enabled) return;
        this.enabled = false;
        this.$el.unbind("click",this.toggle);
        this.$el.addClass("disabled");
    },
    enable:function(){
        if(this.enabled) return;
        this.enabled = true;
        this.$el.click(this.toggle);
        this.$el.removeClass("disabled");
    }
});

var DropDownView = Backbone.View.extend({
    initialize:function(){
        _(this).bindAll("toggle","hide");
    },
    render:function(){
        this.container = this.$el.find(".dropdownBox");
        this.$el.find(".select").unbind().click(this.toggle);
        $('html').click(this.hide);
        this.items = this.$el.find(".dropdownBox a");
        var _this = this;
        this.items.unbind().click(function(ev){
            var el = $(this);
            _this.deselect();
            _this.hide();
            el.addClass("active");
            ev.stopPropagation();
            _this.trigger("select",el);
        });
    },
    hide:function(ev){
        this.container.addClass("off");
        if(ev!=undefined) ev.stopPropagation();
    },
    deselect:function(){
        this.items.removeClass("active");
    },
    toggle: function(ev){
        if(this.container.hasClass("off")){
            $(".dropdownBox").addClass("off");
            this.container.removeClass("off");
            this.trigger("focus");
        }else{
            this.container.addClass("off")
        }
        ev.stopPropagation();
    }
});

var SelectView = DropDownView.extend({

    initialize:function(options){
        DropDownView.prototype.initialize.call(this, options);
        this.hdr = this.$el.find(".select");
    },
    render:function(){
        DropDownView.prototype.render.call(this);
        if(this.hdr.empty()){
            this.select(this.$el.find(".dropdownBox a:first"));
        }else{
            this.data = this.hdr.attr("rel");
        }
        this.on("select",this.select);
    },
    select:function(src){
        if(typeof src == "string"){
            this.hdr.html(this.$el.find(".dropdownBox a[rel="+src+"]").html());
            this.data = src;
        }else{
            this.hdr.html(src.html());
            this.data = src.attr("rel");
        }
        this.trigger("change", this.val());
    },
    val:function(){
        return this.data||this.hdr.html();
    },
    text: function(){
        return this.hdr.html();
    }
});

