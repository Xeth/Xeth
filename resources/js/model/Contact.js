var Contact = Backbone.Model.extend({

    idAttribute: "alias",

    save:function(){
        if(this.isNew()){

            return addressbook.addContact(this.toJSON());
        }else{

            return addressbook.editContact(this.toJSON());
        }
    },

    destroy:function(){
        return addressbook.removeContact(this.get("alias"));
    },

    sync:function(){}

});
