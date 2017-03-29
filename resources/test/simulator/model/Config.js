var ConfigSimulator = Backbone.Model.extend({

    get: function(name){
        return name;
    },

    getFlag: function(name){
        return true;
    },

    setFlag:function(name, val){
        return true;
    },

    set: function(name, value){
        this.triggerChange(name, value);
        return true;
    },

    triggerChange: function(name, value){
        this.trigger("change", this);
        this.trigger("change:"+value, this, value);
    }
});
