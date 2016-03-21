var Config = Backbone.Model.extend({

    get: function(name){
        return XETH_config.get(name);
    },

    set: function(name, value){
        if(XETH_config.set({name: name, value:value}))
        {
            this.triggerChange(name, value);
            return true;
        }
        return false;
    },

    observe: function(){
        XETH_event.Config.connect(this, this.triggerChange);
    },

    triggerChange: function(name, value){
        this.trigger("change", this);
        this.trigger("change:"+value, this, value);
    }
});
