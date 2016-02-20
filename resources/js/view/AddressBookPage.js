var ContactView = Backbone.View.extend({

    initialize:function(options){
        _(this).bindAll("updateAlias", "updateAddress", "updateAvatar", "updateBitProfile", "editName", "removeLater", "cancelRemove");
        var data = {contact:this.model.toJSON()};
        this.$el = $(options.template(data));
        this.listenTo(this.model, "change:alias", this.updateAlias);
        this.listenTo(this.model, "change:address", this.updateAddress);
        this.listenTo(this.model, "change:avatar", this.updateAvatar);
        this.listenTo(this.model, "change:bitprofile", this.updateBitProfile);
        this.listenTo(this.model, "change:transactions", this.updateTransactions);

        this.$el.find('.name.editableTxt').editable({
            mode: 'inline',
            autotext: 'always',
            clear: false,
            validate: this.editName,
            display: false
        });

        this.$el.find(".remove").click(this.removeLater);
        this.$el.find(".removing .cancel").click(this.cancelRemove);

    },

    updateAlias:function(){
        this.$el.find(".name").html(this.model.get("alias"));
    },

    updateAddress:function(){
        this.$el.find(".address").html(this.model.get("address"));
    },

    updateAvatar:function(){
        this.$el.find(".avatar img").attr("src", this.model.get("avatar"));
    },

    updateBitProfile:function(){
        var icon = this.$el.find(".bitprofileIcon");
        var bitprofile = this.model.get("bitprofile");

        if(bitprofile){
            if(!icon.hasClass("on")) icon.addClass("on");
            icon.attr("title", bitprofile);
        }else{
            icon.removeClass("on");
        }
    },

    updateTransactions:function(){
        this.$el.find(".transactions").html(this.model.get("transactions"));
    },

    editName:function(name){
        this.model.set({alias:name});
        this.model.save();
    },

    removeLater:function(){
        this.$el.addClass("removing");
        var counter = 5;
        var model = this.model;
        var $el = this.$el.find(".removing .time");
        $el.html(counter);
        var timer = this.timer = setInterval(function(){
            counter--;
            if(counter<0){
                clearInterval(timer);
                model.destroy();
            }else{
                $el.html(counter);
            }
        }, 1000);
    },

    cancelRemove:function(){
        if(this.timer) clearInterval(this.timer);
        this.$el.removeClass("removing");
    }


});

function ContactViewFactory(){
    var template = _.template($("#contact_item_tpl").html());
    this.create = function(model){return new ContactView({model:model, template:template})}
    return this;
}


var AddressBookPageView = Backbone.View.extend({

    initialize:function(options){
        _(this).bindAll("applyFilter");

        this.template = _.template($("#addressbook_tpl").html());
        this.$el.html(this.template())
        this.collection = new CollectionView({el: this.$el.find(".addressbook .holder"), collection: options.addressbook, factory:new ContactViewFactory});
        this.collection.render();
        this.$filter = this.$el.find("#filterContacts select");
        this.$filter.change(this.applyFilter);
    },

    applyFilter:function(){
        var criterion = this.$filter.val();
        if(criterion=="all"){
            this.collection.filter(function(){return true;});
        }
        else{
            var local = (criterion!="bitprofile");
            this.collection.filter(function(model){return local == !model.get("bitprofile"); });
        }
    }


})
